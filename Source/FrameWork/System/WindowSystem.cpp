#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <assert.h>

#include "FrameWork/System/WindowSystem.h"
#include "FrameWork/System/EventSystem.h"
#include "Front/Config/Constants.h"

// 規定2: Allmanスタイルを採用
namespace EngineCore
{
    WindowSystem::WindowSystem()
        : m_Hwnd(nullptr)
        , m_ShouldClose(false)
    {
    }

    // ウィンドウプロシージャ
    LResult CALLBACK WindowSystem::WindowProc(HWND hwnd, UInt u_msg, WParam w_param, LParam l_param)
    {
        WindowSystem* p_this = nullptr;

        if (u_msg == WM_NCCREATE)
        {
            // CreateWindowEx の最後の引数 (this) を取り出す
            LPCREATESTRUCTW p_create = reinterpret_cast<LPCREATESTRUCTW>(l_param);
            p_this = reinterpret_cast<WindowSystem*>(p_create->lpCreateParams);
            // HWND に自分自身のポインタを刻む
            SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_this));
        }
        else
        {
            // 刻んでおいたポインタを取り出す
            p_this = reinterpret_cast<WindowSystem*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
        }

        // EventSystem が接続されていれば、メッセージを配送
        if (p_this && p_this->m_pEventSystem)
        {
            p_this->m_pEventSystem->PushEvent(hwnd, u_msg, w_param, l_param);
        }

        switch (u_msg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcW(hwnd, u_msg, w_param, l_param);
        }
    }

    // 引数なしに変更。ヘッダの宣言と一致させる
    [[nodiscard]] HResult WindowSystem::Init()
    {
        // m_pEventSystem は事前に SetEventSystem で設定されている前提
        HINSTANCE h_instance = GetModuleHandle(nullptr);

        // 1. ウィンドウクラスの登録
        WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WindowProc;
        wcex.cbClsExtra = 0; // 追加
        wcex.cbWndExtra = 0; // 追加
        wcex.hInstance = h_instance;
        wcex.lpszClassName = kWindowClassName;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hIcon = nullptr; // 追加

        if (!RegisterClassExW(&wcex)) return kEFail;

        RECT rc = { 0, 0, kDefaultWindowWidth, kDefaultWindowHeight };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        // 3. ウィンドウ生成 (引数は合計12個必要)
        m_Hwnd = CreateWindowExW(
            0,
            kWindowClassName,
            kEngineName,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rc.right - rc.left,
            rc.bottom - rc.top,
            nullptr,    // hWndParent
            nullptr,    // hMenu
            h_instance,
            this        // lpParam (12個目)
        );

        if (!m_Hwnd) return kEFail;

        ShowWindow(m_Hwnd, SW_SHOW);
        UpdateWindow(m_Hwnd);

        return kSOk;
    }

    void WindowSystem::Update(float delta_time)
    {
        MSG msg = {};
        // OSからのメッセージを収集
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // WindowProc で投げられた PostQuitMessage(0) をここで検知する
            if (msg.message == WM_QUIT)
            {
                m_ShouldClose = true;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void WindowSystem::UnInit()
    {
        if (m_Hwnd)
        {
            DestroyWindow(m_Hwnd);
            m_Hwnd = nullptr;
        }
        UnregisterClassW(kWindowClassName, GetModuleHandle(nullptr));
    }
}