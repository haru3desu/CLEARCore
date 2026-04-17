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
    using Int = int;
    using UInt = unsigned int;
    using HResult = long;

#ifdef FAILED
#undef FAILED
#endif
#ifdef SUCCEEDED
#undef SUCCEEDED
#endif

#define FAILED(hr) (((long)(hr)) < 0)
#define SUCCEEDED(hr) (((long)(hr)) >= 0)

    static constexpr HResult kSOk = 0L;
    static constexpr HResult kEFail = 0x80004005L;

    // メッセージ処理用の基本型エイリアス
    using LResult = long long;
    using WParam = unsigned __int64;
    using LParam = long long;
}