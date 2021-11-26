#pragma once

extern bool g_MenuEnable;

extern bool g_ImplWin32Init;

extern WNDPROC g_OriginalWndProc;

extern D3DPRESENT_PARAMETERS g_d3dPresent;

bool ImGui_ImplWin32_Init();

void ImGui_ImplWin32_NewFrame();

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
