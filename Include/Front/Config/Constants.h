#pragma once
//====================================================
// Constants.h
// エンジン全体で使用する定数定義
// 規定に基づき、0, 1, -1 以外の数値はすべてここで管理する。
//====================================================

namespace EngineCore {
    // ウィンドウ設定
    static constexpr int kDefaultWindowWidth = 1280;
    static constexpr int kDefaultWindowHeight = 720;

    // 文字列定数
    static constexpr const wchar_t* kEngineName = L"CLEARCore Engine";
    static constexpr const wchar_t* kWindowClassName = L"CLEARCoreWindowClass";

    // --- キー定義 (KeyCode) ---
    // Windows の VK_* と値を一致させておくことで、InputSystem 内での変換コストをゼロにする
    enum class KeyCode : int
    {
        kSpace = 0x20, // VK_SPACE
        kReturn = 0x0D, // VK_RETURN
        kEscape = 0x1B, // VK_ESCAPE
        kLeft = 0x25,
        kUp = 0x26,
        kRight = 0x27,
        kDown = 0x28,
        kKeyA = 0x41,
        kKeyD = 0x44,
        kKeyS = 0x53,
        kKeyW = 0x57,
        // 必要に応じて追加
    };

}