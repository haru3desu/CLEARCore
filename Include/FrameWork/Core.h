#pragma once

#include <memory>
#include <vector>
#include "FrameWork/Interface/ISystem.h"

namespace EngineCore
{
    // --- 前方宣言 ---
    class WindowSystem;
    class InputSystem;

    class Core
    {
    public:
        Core();
        ~Core() = default;

        // システムの外部登録
        void AddSystem(std::unique_ptr<ISystem> p_system);

        [[nodiscard]] HResult Run();

    private:
        [[nodiscard]] HResult Init();
        void UnInit();
        void Update();

        bool m_IsRunning;
        std::vector<std::unique_ptr<ISystem>> m_Systems;

        // WindowSystem への参照（終了判定用）
        WindowSystem* m_pWindowSystem;
        InputSystem* m_pInputSystem;
    };
}