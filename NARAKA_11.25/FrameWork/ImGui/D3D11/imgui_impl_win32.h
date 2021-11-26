#pragma once

extern bool g_MenuEnable;

extern bool g_ImplWin32Init;

extern WNDPROC g_OriginalWndProc;

extern DXGI_SWAP_CHAIN_DESC g_d3dDes;

bool ImGui_ImplWin32_Init();

void ImGui_ImplWin32_NewFrame();

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
