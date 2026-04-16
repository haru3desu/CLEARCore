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
}