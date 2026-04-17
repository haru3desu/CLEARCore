#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Front/Config/Constants.h"
#include "FrameWork/Interface/ISystem.h"


namespace EngineCore
{
    class EventSystem;

    class InputSystem : public ISystem
    {
    public:
        InputSystem();
        virtual ~InputSystem() = default;

        [[nodiscard]] virtual HResult Init() override;
        virtual void UnInit() override;
        virtual void Update(float delta_time) override;

        virtual EngineCore::SystemPriority GetPriority() const override { return EngineCore::SystemPriority::kPreUpdate; }
        // EventSystem を接続
        void SetEventSystem(EventSystem* p_event_system) { m_pEventSystem = p_event_system; }

        // --- 基本入力判定 ---
        bool IsKey(KeyCode key_code) const;     // 押されている間ずっと
        bool IsKeyDown(KeyCode key_code) const; // 押された瞬間
        bool IsKeyUp(KeyCode key_code) const;   // 離された瞬間

        bool IsActionDown(const std::string& action_name) const;

    private:
        EventSystem* m_pEventSystem;

        // キー状態管理（256個の仮想キーコードをカバー）
        // 0: 離れている, 1: 押された瞬間, 2: 押されている, 3: 離された瞬間
        unsigned char m_KeyStates[256];
        unsigned char m_PrevKeyStates[256];

        // キーコンフィグ用
        std::unordered_map<std::string, KeyCode> m_KeyMap;
    };
}