#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <crtdbg.h>

#include "FrameWork/Core.h"

/**
 * @brief エントリーポイント
 */
int WINAPI WinMain(_In_ HINSTANCE h_instance, _In_opt_ HINSTANCE h_prev_instance, _In_ LPSTR lp_cmd_line, _In_ int n_cmd_show)
{
    // メモリリーク検出の有効化
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto p_core = std::make_unique<EngineCore::Core>();

    if (FAILED(p_core->Run()))
    {
        return -1;
    }

    return 0;
}