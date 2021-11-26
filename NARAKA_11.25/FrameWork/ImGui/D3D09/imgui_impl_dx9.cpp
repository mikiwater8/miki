#include "stdafx.h"

struct CustomVertex
{
	float pos[3];
	D3DCOLOR col;
	float uv[2];
};

int g_MenuStyle = 1;

bool g_ImplDX9Init = false;

D3DVIEWPORT9 g_d3dViewPort;

LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

LPDIRECT3DSWAPCHAIN9 g_pd3dSwapChain = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;

LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;

LPDIRECT3DTEXTURE9 g_FontTexture = NULL;

INT g_VertexBufferSize = 5000, g_IndexBufferSize = 10000;

void ImGui_ImplDX9_RenderDrawData(ImDrawData* draw_data)
{
	if (draw_data->DisplaySize.x > 0.0f && draw_data->DisplaySize.y > 0.0f)
	{
		IDirect3DStateBlock9* pStateBlock;

		if (g_pd3dDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock) == 0)
		{
			CustomVertex* vtx_dst;

			ImDrawIdx* idx_dst;

			if (!g_pVB || g_VertexBufferSize < draw_data->TotalVtxCount)
			{
				if (g_pVB)
				{
					g_pVB->Release();

					g_pVB = NULL;
				}

				g_VertexBufferSize = draw_data->TotalVtxCount + 5000;

				if (g_pd3dDevice->CreateVertexBuffer(g_VertexBufferSize * sizeof(CustomVertex), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1, D3DPOOL_DEFAULT, &g_pVB, NULL) < 0)
				{
					return;
				}
			}

			if (!g_pIB || g_IndexBufferSize < draw_data->TotalIdxCount)
			{
				if (g_pIB)
				{
					g_pIB->Release();

					g_pIB = NULL;
				}

				g_IndexBufferSize = draw_data->TotalIdxCount + 10000;

				if (g_pd3dDevice->CreateIndexBuffer(g_IndexBufferSize * sizeof(ImDrawIdx), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, sizeof(ImDrawIdx) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, &g_pIB, NULL) < 0)
				{
					return;
				}
			}

			if (g_pVB->Lock(NULL, (UINT)(draw_data->TotalVtxCount * sizeof(CustomVertex)), (void**)&vtx_dst, D3DLOCK_DISCARD) < 0)
			{
				return;
			}

			if (g_pIB->Lock(NULL, (UINT)(draw_data->TotalIdxCount * sizeof(ImDrawIdx)), (void**)&idx_dst, D3DLOCK_DISCARD) < 0)
			{
				return;
			}

			for (int i = 0; i < draw_data->CmdListsCount; i++)
			{
				const ImDrawList* cmd_list = draw_data->CmdLists[i];

				const ImDrawVert* vtx_src = cmd_list->VtxBuffer.Data;

				for (int ii = 0; ii < cmd_list->VtxBuffer.Size; ii++)
				{
					vtx_dst->pos[0] = vtx_src->pos.x;

					vtx_dst->pos[1] = vtx_src->pos.y;

					vtx_dst->pos[2] = 0.0f;

					vtx_dst->col = (vtx_src->col & 0xFF00FF00) | ((vtx_src->col & 0xFF0000) >> 16) | ((vtx_src->col & 0xFF) << 16);

					vtx_dst->uv[0] = vtx_src->uv.x;

					vtx_dst->uv[1] = vtx_src->uv.y;

					vtx_dst++;

					vtx_src++;
				}

				memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));

				idx_dst += cmd_list->IdxBuffer.Size;
			}

			g_pVB->Unlock();

			g_pIB->Unlock();

			g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CustomVertex));

			g_pd3dDevice->SetIndices(g_pIB);

			g_pd3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

			g_pd3dDevice->SetPixelShader(NULL);

			g_pd3dDevice->SetVertexShader(NULL);

			g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

			g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

			g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

			g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

			g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

			g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

			g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

			g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

			float L = draw_data->DisplayPos.x + 0.5f;

			float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x + 0.5f;

			float T = draw_data->DisplayPos.y + 0.5f;

			float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y + 0.5f;

			D3DMATRIX mat_identity = { { { 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f } } };

			D3DMATRIX mat_projection = { { { 2.0f / (R - L), 0.0f, 0.0f,  0.0f, 0.0f, 2.0f / (T - B), 0.0f,  0.0f, 0.0f, 0.0f, 0.5f,  0.0f, (L + R) / (L - R), (T + B) / (B - T), 0.5f, 1.0f } } };

			g_pd3dDevice->SetTransform(D3DTS_WORLD, &mat_identity);

			g_pd3dDevice->SetTransform(D3DTS_VIEW, &mat_identity);

			g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat_projection);

			int global_vtx_offset = 0;

			int global_idx_offset = 0;

			ImVec2 clip_off = draw_data->DisplayPos;

			for (int i = 0; i < draw_data->CmdListsCount; i++)
			{
				const ImDrawList* cmd_list = draw_data->CmdLists[i];

				for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
				{
					const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

					if (pcmd->UserCallback != NULL)
					{
						if (pcmd->UserCallback != ImDrawCallback_ResetRenderState)
						{
							pcmd->UserCallback(cmd_list, pcmd);
						}
					}
					else
					{
						const RECT r = { (LONG)(pcmd->ClipRect.x - clip_off.x), (LONG)(pcmd->ClipRect.y - clip_off.y), (LONG)(pcmd->ClipRect.z - clip_off.x), (LONG)(pcmd->ClipRect.w - clip_off.y) };

						const LPDIRECT3DTEXTURE9 texture = (LPDIRECT3DTEXTURE9)pcmd->TextureId;

						g_pd3dDevice->SetTexture(0, texture);

						g_pd3dDevice->SetScissorRect(&r);

						g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, pcmd->VtxOffset + global_vtx_offset, 0, (UINT)cmd_list->VtxBuffer.Size, pcmd->IdxOffset + global_idx_offset, pcmd->ElemCount / 3);
					}
				}

				global_idx_offset += cmd_list->IdxBuffer.Size;

				global_vtx_offset += cmd_list->VtxBuffer.Size;
			}

			pStateBlock->Apply();

			pStateBlock->Release();
		}
	}
}

void ImGui_ImplDX9_CreateFontsTexture()
{
	ImGuiIO& io = ImGui::GetIO();

	unsigned char* Pixels;

	int Width, Height, BytesPerPixel;

	io.Fonts->GetTexDataAsRGBA32(&Pixels, &Width, &Height, &BytesPerPixel);

	g_pd3dDevice->CreateTexture(Width, Height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_FontTexture, NULL);

	D3DLOCKED_RECT TexLockedRect = { 0 };

	g_FontTexture->LockRect(0, &TexLockedRect, NULL, 0);

	for (int y = 0; y < Height; y++)
	{
		memcpy((unsigned char *)TexLockedRect.pBits + TexLockedRect.Pitch * y, Pixels + (Width * BytesPerPixel) * y, (Width * BytesPerPixel));
	}

	g_FontTexture->UnlockRect(0);

	io.Fonts->TexID = (ImTextureID)g_FontTexture;
}

void ImGui_ImplDX9_NewFrame()
{
	if (g_pd3dDevice->GetViewport(&g_d3dViewPort) == S_OK)
	{
		ImGuiIO& io = ImGui::GetIO();

		g_d3dViewPort.X = g_d3dViewPort.Width / 2;

		g_d3dViewPort.Y = g_d3dViewPort.Height / 2;

		io.DisplaySize = ImVec2((FLOAT)g_d3dViewPort.Width, (FLOAT)g_d3dViewPort.Height);
	}
}

bool ImGui_ImplDX9_Init()
{
	if (g_ImplDX9Init == true)
	{
		return true;
	}
	else
	{
		if (g_pd3dDevice && g_pd3dDevice->GetSwapChain(NULL, &g_pd3dSwapChain) == S_OK)
		{
			ImGuiContext* GImGui = ImGui::GetCurrentContext();

			if (GImGui)
				ImGui::DestroyContext(GImGui);

			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO();

			io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

			ImGui_ImplDX9_CreateFontsTexture();

			g_ImplDX9Init = true;
		}
	}

	return false;
}

void ImGui_ImplDX9_Shutdown()
{
	if (!g_pd3dDevice)
	{
		return;
	}

	if (g_pVB)
	{
		g_pVB->Release();
		g_pVB = NULL;
	}

	if (g_pIB)
	{
		g_pIB->Release();
		g_pIB = NULL;
	}

	ImGuiIO& io = ImGui::GetIO();

	if (g_FontTexture)
	{
		g_FontTexture->Release();
	}

	g_FontTexture = NULL;

	io.Fonts->TexID = NULL;

	g_pd3dDevice = NULL;

	g_ImplDX9Init = false;
}