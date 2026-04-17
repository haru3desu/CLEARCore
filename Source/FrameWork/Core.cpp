#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>


#include "FrameWork/Core.h"
#include <algorithm>
#include <assert.h>
#include "FrameWork/System/WindowSystem.h"
#include "FrameWork/System/EventSystem.h"
#include "FrameWork/System/InputSystem.h"

namespace EngineCore
{
    Core::Core()
        : m_IsRunning(false)
        , m_pWindowSystem(nullptr)
    {
    }

    void Core::AddSystem(std::unique_ptr<ISystem> p_system)
    {
        m_Systems.push_back(std::move(p_system));

        // 優先度順に昇順ソート
        std::sort(m_Systems.begin(), m_Systems.end(), [](const auto& a, const auto& b)
            {
                return static_cast<int>(a->GetPriority()) < static_cast<int>(b->GetPriority());
            });
    }

    [[nodiscard]] HResult Core::Init()
    {
        // 1. EventSystem (実体は最後に Update されるが、ポインタは先に必要)
        auto p_event = std::make_unique<EventSystem>();
        EventSystem* p_event_raw = p_event.get();
        AddSystem(std::move(p_event));

        // 2. WindowSystem
        auto p_window = std::make_unique<WindowSystem>();
        m_pWindowSystem = p_window.get();
        p_window->SetEventSystem(p_event_raw);
        if (FAILED(p_window->Init())) return kEFail;
        AddSystem(std::move(p_window));

        // 3. InputSystem
        auto p_input = std::make_unique<InputSystem>();
        m_pInputSystem = p_input.get(); // メンバに保持
        m_pInputSystem->SetEventSystem(p_event_raw);

        if (FAILED(m_pInputSystem->Init())) return kEFail;
        AddSystem(std::move(p_input));

        // 全てのシステムを Init 済みの状態で登録完了
        m_IsRunning = true;
        return kSOk;
    }

    [[nodiscard]] HResult Core::Run()
    {
        if (FAILED(Init()))
        {
            return kEFail;
        }

        while (m_IsRunning)
        {
            Update();
        }

        UnInit();
        return kSOk;
    }

    void Core::Update()
    {
        constexpr float kDeltaTime = 0.016f;

        for (auto& p_system : m_Systems)
        {
            p_system->Update(kDeltaTime);
        }

        // dynamic_cast ループを削除し、メンバを直接使用
        if (m_pInputSystem)
        {
            if (m_pInputSystem->IsKeyDown(KeyCode::kSpace))
            {
                OutputDebugStringA(">> [Input Test] Optimized Space Check\n");
            }
        }

        if (m_pWindowSystem && m_pWindowSystem->ShouldClose())
        {
            m_IsRunning = false;
        }
    }

    void Core::UnInit()
    {
        // 逆順で破棄
        for (auto it = m_Systems.rbegin(); it != m_Systems.rend(); ++it)
        {
            (*it)->UnInit();
        }
        m_Systems.clear();
    }
}