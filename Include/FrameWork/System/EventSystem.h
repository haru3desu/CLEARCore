#pragma once
#include "FrameWork/Interface/ISystem.h"
#include <vector>

namespace EngineCore
{
    // メッセージデータをパケット化
    struct WindowMessage
    {
        HWND Hwnd;
        UInt Msg;
        WParam WP;
        LParam LP;
    };

    class EventSystem : public ISystem
    {
    public:
        EventSystem();
        virtual ~EventSystem() = default;

        [[nodiscard]] virtual HResult Init() override;
        virtual void UnInit() override;
        virtual void Update(float delta_time) override;

        virtual SystemPriority GetPriority() const override { return SystemPriority::kEventCleanup; }

        // WindowSystem から呼ばれる
        void PushEvent(HWND hwnd, UInt u_msg, WParam w_param, LParam l_param);

        /**
     * @brief 蓄積された全イベントを取得
     * @return イベントパケットのリスト（読み取り専用）
     */
        [[nodiscard]] const std::vector<WindowMessage>& GetEvents() const { return m_EventQueue; }
    private:
        std::vector<WindowMessage> m_EventQueue;
    };
}