#pragma once
//====================================================
// ISystem.h
//====================================================
#include "FrameWork/CoreTypes.h"

namespace EngineCore
{
    enum class SystemPriority : int
    {
        kWindow = 0,   // Window, Input
        kPreUpdate = 10,   // Window, Input
        kLogic = 100, // Actor, Script
        kPhysics = 200, // Collision, Physics
        kPostUpdate = 300, // Camera, Audio
        kRender = 400, // Rendering
        kEventCleanup = 999, // EventSystem::Update (clear) は最後に実行
    };

    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        [[nodiscard]] virtual HResult Init() = 0;
        virtual void UnInit() = 0;
        virtual void Update(float delta_time) = 0;

        // システムの実行優先度を取得
        virtual SystemPriority GetPriority() const = 0;
    };
}