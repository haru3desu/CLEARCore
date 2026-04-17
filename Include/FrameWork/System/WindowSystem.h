#pragma once
//====================================================
// WindowSystem.h
//====================================================

#include "FrameWork/Interface/ISystem.h"

namespace EngineCore {
    // 前方宣言
    class EventSystem;

    class WindowSystem : public ISystem
    {
    public:
        WindowSystem();
        virtual ~WindowSystem() = default;

        [[nodiscard]] virtual HResult Init() override;
        virtual void UnInit() override;
        virtual void Update(float delta_time) override;

        void SetEventSystem(EventSystem* p_event_system) { m_pEventSystem = p_event_system; }

        // 外部（Core等）から終了状態を確認するためのゲッター
        bool ShouldClose() const { return m_ShouldClose; }
    private:
        // OSからのメッセージを捌く窓口（プロシージャ）
        static LResult CALLBACK WindowProc(HWND hwnd, UInt u_msg, WParam w_param, LParam l_param);
        virtual SystemPriority GetPriority() const override { return SystemPriority::kWindow; }

        HWND m_Hwnd;
        bool m_ShouldClose;
        EventSystem* m_pEventSystem;
    };
}