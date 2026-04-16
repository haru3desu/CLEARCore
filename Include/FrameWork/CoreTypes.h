#pragma once

// --- Windows 固有型の前方宣言 (グローバル) ---
#ifndef _HWND_DEFINED
#define _HWND_DEFINED
struct HWND__;
typedef struct HWND__* HWND;
#endif

#ifndef _HINSTANCE_DEFINED
#define _HINSTANCE_DEFINED
struct HINSTANCE__;
typedef struct HINSTANCE__* HINSTANCE;
#endif

// CALLBACK は __stdcall という呼び出し規約のマクロ。Windows.h なしの時は自前で定義。
#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

namespace EngineCore
{
    using HResult = long;

#ifndef FAILED
#define FAILED(hr) (((long)(hr)) < 0)
#endif

#ifndef SUCCEEDED
#define SUCCEEDED(hr) (((long)(hr)) >= 0)
#endif

    static constexpr HResult kSOk = 0L;
    static constexpr HResult kEFail = 0x80004005L;

    // メッセージ処理用の基本型エイリアス
    using LResult = long long;
    using WParam = unsigned __int64;
    using LParam = long long;
    using UInt = unsigned int;
}