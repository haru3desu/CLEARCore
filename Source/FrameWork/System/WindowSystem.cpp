#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <assert.h>

#include "FrameWork/System/WindowSystem.h"
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
        switch (u_msg)
        {
        case WM_DESTROY:
            // 「×」ボタン等が押された際、OSのメッセージキューに WM_QUIT を投げる
            PostQuitMessage(0);
            return 0;

        default:
            // 興味のないメッセージはOSの標準処理に任せる
            return DefWindowProcW(hwnd, u_msg, w_param, l_param);
        }
    }

    [[nodiscard]] HResult WindowSystem::Init()
    {
        HINSTANCE h_instance = GetModuleHandle(nullptr);

        // 1. ウィンドウクラスの登録
        WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WindowProc;
        wcex.hInstance = h_instance;
        wcex.lpszClassName = kWindowClassName;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

        if (!RegisterClassExW(&wcex))
        {
            return kEFail;
        }

        // 2. ウィンドウサイズの計算（クライアント領域を Constants.h の値に合わせる）
        RECT rc = { 0, 0, kDefaultWindowWidth, kDefaultWindowHeight };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        // 3. ウィンドウ生成
        m_Hwnd = CreateWindowExW(
            0,
            kWindowClassName,
            kEngineName,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rc.right - rc.left,
            rc.bottom - rc.top,
            nullptr,
            nullptr,
            h_instance,
            nullptr
        );

        if (!m_Hwnd)
        {
            return kEFail;
        }

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