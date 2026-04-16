#pragma once
//====================================================
// WindowSystem.h
//====================================================

#include "FrameWork/Interface/ISystem.h"

namespace EngineCore {
    class WindowSystem : public ISystem
    {
    public:
        WindowSystem();
        virtual ~WindowSystem() = default;

        [[nodiscard]] virtual HResult Init() override;
        virtual void UnInit() override;
        virtual void Update(float delta_time) override;

        // 外部（Core等）から終了状態を確認するためのゲッター
        bool ShouldClose() const { return m_ShouldClose; }
    private:
        // OSからのメッセージを捌く窓口（プロシージャ）
        static LResult CALLBACK WindowProc(HWND hwnd, UInt u_msg, WParam w_param, LParam l_param);

        HWND m_Hwnd;
        bool m_ShouldClose;
    };
}