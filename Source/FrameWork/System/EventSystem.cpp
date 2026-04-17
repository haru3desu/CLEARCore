#include "FrameWork/System/EventSystem.h"

namespace EngineCore
{
    EventSystem::EventSystem()
    {
    }

    [[nodiscard]] HResult EventSystem::Init()
    {
        return kSOk;
    }

    void EventSystem::UnInit()
    {
        m_EventQueue.clear();
    }

    void EventSystem::Update(float delta_time)
    {
        // 1フレーム前のイベントを破棄
        m_EventQueue.clear();
    }

    void EventSystem::PushEvent(HWND hwnd, UInt u_msg, WParam w_param, LParam l_param)
    {
        m_EventQueue.push_back({ hwnd, u_msg, w_param, l_param });
    }
}