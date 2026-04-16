#include "FrameWork/Core.h"
#include <assert.h>
#include "FrameWork/System/WindowSystem.h"

namespace EngineCore
{
    Core::Core()
        : m_IsRunning(false)
    {
    }

    [[nodiscard]] HResult Core::Init()
    {
        // ‹K’è2: unique_ptr ‚ðŽg—p
        // WindowSystem ‚Ì“o˜^
        auto p_window = std::make_unique<WindowSystem>();
        if (FAILED(p_window->Init()))
        {
            assert(false && "Failed to Initialize WindowSystem.");
            return kEFail;
        }
        m_Systems.push_back(std::move(p_window));

        // ¡ŒãAEventSystem ‚â InputSystem ‚à“¯—l‚É“o˜^

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
        constexpr float kDeltaTime = 0.016f; // ‰¼‚ÌŒÅ’è’l

        for (auto& p_system : m_Systems)
        {
            p_system->Update(kDeltaTime);
        }

        // ‚±‚±‚Å WindowSystem ‚Ì ShouldClose() “™‚ðƒ`ƒFƒbƒN‚µ‚Ä m_IsRunning ‚ð§Œä‚·‚éƒƒWƒbƒN‚ª•K—v
    }

    void Core::UnInit()
    {
        // ‹t‡‚Å”jŠü
        for (auto it = m_Systems.rbegin(); it != m_Systems.rend(); ++it)
        {
            (*it)->UnInit();
        }
        m_Systems.clear();
    }
}