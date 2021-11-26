#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;

extern bool g_ImplDX11Init;

extern D3D11_VIEWPORT g_d3dViewPort;

extern IDXGISwapChain* g_pd3dSwapChain;
extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pd3dDeviceContext;
extern IDXGIFactory* g_pFactory;
extern ID3D11Buffer* g_pVB;
extern ID3D11Buffer* g_pIB;
extern ID3D10Blob* g_pVertexShaderBlob;
extern ID3D11VertexShader* g_pVertexShader;
extern ID3D11InputLayout* g_pInputLayout;
extern ID3D11Buffer* g_pVertexConstantBuffer;
extern ID3D10Blob* g_pPixelShaderBlob;
extern ID3D11PixelShader* g_pPixelShader;
extern ID3D11SamplerState* g_pFontSampler;
extern ID3D11ShaderResourceView*g_pFontTextureView;
extern ID3D11RasterizerState* g_pRasterizerState;
extern ID3D11BlendState* g_pBlendState;
extern ID3D11DepthStencilState* g_pDepthStencilState;
extern ID3D11RenderTargetView* g_pRenderTargetView;

void ImGui_ImplDX11_RenderDrawData(ImDrawData* draw_data);
bool ImGui_ImplDX11_Init(IDXGISwapChain* pSwapChain);
void ImGui_ImplDX11_NewFrame();
void ImGui_ImplDX11_Shutdown();