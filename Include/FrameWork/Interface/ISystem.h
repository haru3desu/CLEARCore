#pragma once
//====================================================
// ISystem.h
//====================================================
#include "FrameWork/CoreTypes.h"
namespace EngineCore
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        // システムの初期化
        [[nodiscard]] virtual HResult Init() = 0;

        // システムの解放
        virtual void UnInit() = 0;

        // フレーム更新
         // delta_time 前フレームからの経過時間
        virtual void Update(float delta_time) = 0;
    };
}