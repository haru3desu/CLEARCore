#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include "FrameWork/System/InputSystem.h"
#include "FrameWork/System/EventSystem.h"

namespace EngineCore
{
    InputSystem::InputSystem()
        : m_pEventSystem(nullptr)
    {
        for (int i = 0; i < 256; ++i)
        {
            m_KeyStates[i] = 0;
            m_PrevKeyStates[i] = 0;
        }
    }

    [[nodiscard]] HResult InputSystem::Init()
    {
        // キーコンフィグの基礎データ (Constants.h の KeyCode を使用)
        m_KeyMap["Jump"] = KeyCode::kSpace;
        m_KeyMap["Submit"] = KeyCode::kReturn;
        return kSOk;
    }

    void InputSystem::UnInit()
    {
        m_KeyMap.clear();
    }

    void InputSystem::Update(float delta_time)
    {
        if (!m_pEventSystem) return;

        // 1. 前フレームの状態をコピー
        for (int i = 0; i < 256; ++i)
        {
            m_PrevKeyStates[i] = m_KeyStates[i];
        }

        // 2. EventSystem からイベントを抽出して解析
        const auto& events = m_pEventSystem->GetEvents();
        for (const auto& event : events)
        {
            switch (event.Msg)
            {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                if (event.WP < 256) m_KeyStates[event.WP] = 1;
                break;

            case WM_KEYUP:
            case WM_SYSKEYUP:
                if (event.WP < 256) m_KeyStates[event.WP] = 0;
                break;

            case WM_ACTIVATE:
                if (LOWORD(event.WP) == WA_INACTIVE)
                {
                    for (int i = 0; i < 256; ++i) m_KeyStates[i] = 0;
                }
                break;
            }
        }
    }

    // --- 判定関数（範囲チェックを追加し安全性を担保） ---

    bool InputSystem::IsKey(KeyCode key_code) const
    {
        const int code = static_cast<int>(key_code);
        if (code < 0 || code >= 256) return false;
        return m_KeyStates[code] == 1;
    }

    bool InputSystem::IsKeyDown(KeyCode key_code) const
    {
        const int code = static_cast<int>(key_code);
        if (code < 0 || code >= 256) return false;
        return (m_KeyStates[code] == 1) && (m_PrevKeyStates[code] == 0);
    }

    bool InputSystem::IsKeyUp(KeyCode key_code) const
    {
        const int code = static_cast<int>(key_code);
        if (code < 0 || code >= 256) return false;
        return (m_KeyStates[code] == 0) && (m_PrevKeyStates[code] == 1);
    }

    bool InputSystem::IsActionDown(const std::string& action_name) const
    {
        auto it = m_KeyMap.find(action_name);
        if (it != m_KeyMap.end())
        {
            return IsKeyDown(it->second);
        }
        return false;
    }
}