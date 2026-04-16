#pragma once

#include <memory>
#include <vector>
#include "FrameWork/Interface/ISystem.h"

namespace EngineCore
{
    class Core
    {
    public:
        Core();
        ~Core() = default;

        [[nodiscard]] HResult Run();

    private:
        [[nodiscard]] HResult Init();
        void UnInit();
        void Update();

        bool m_IsRunning;
        std::vector<std::unique_ptr<ISystem>> m_Systems;
    };
}