#pragma once

struct IDirect3DDevice9;

extern D3DVIEWPORT9 g_d3dViewPort;

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

extern LPDIRECT3DSWAPCHAIN9 g_pd3dSwapChain;

extern int g_MenuStyle;

extern bool g_ImplDX9Init;

bool ImGui_ImplDX9_Init();

void ImGui_ImplDX9_Shutdown();

void ImGui_ImplDX9_NewFrame();

void ImGui_ImplDX9_CreateFontsTexture();

void ImGui_ImplDX9_RenderDrawData(ImDrawData* draw_data);
