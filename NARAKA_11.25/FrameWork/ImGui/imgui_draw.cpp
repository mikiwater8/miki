#include "stdafx.h"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include "imgui_internal.h"
#include "imstb_rectpack.h"

#define STBTT_malloc(x,u) ((void)(u), ImGui::MemAlloc(x))
#define STBTT_free(x,u) ((void)(u), ImGui::MemFree(x))
#define STBTT_fmod(x,y) ImFmod(x,y)
#define STBTT_sqrt(x) ImSqrt(x)
#define STBTT_pow(x,y) ImPow(x,y)
#define STBTT_fabs(x) ImFabs(x)
#define STBTT_ifloor(x) ((int)ImFloorStd(x))
#define STBTT_iceil(x) ((int)ImCeil(x))

#include "imstb_truetype.h"

void ImGui::StyleColorsDark(ImGuiStyle* dst)
{
	ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.26f, 0.26f, 0.26f, 0.85f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
	colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
	colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
	colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.32f, 0.52f, 0.65f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.75f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

ImDrawListSharedData::ImDrawListSharedData()
{
	Font = NULL;
	FontSize = 0.0f;
	CurveTessellationTol = 0.0f;
	CircleSegmentMaxError = 0.0f;
	ClipRectFullscreen = ImVec4(-8192.0f, -8192.0f, +8192.0f, +8192.0f);
	InitialFlags = ImDrawListFlags_None;

	// Lookup tables
	for (int i = 0; i < ARRAYSIZE(ArcFastVtx); i++)
	{
		const float a = ((float)i * 2 * 3.1415926f) / (float)ARRAYSIZE(ArcFastVtx);
		ArcFastVtx[i] = ImVec2(ImCos(a), ImSin(a));
	}
	memset(CircleSegmentCounts, 0, sizeof(CircleSegmentCounts)); // This will be set by SetCircleSegmentMaxError()
}

void ImDrawListSharedData::SetCircleSegmentMaxError(float max_error)
{
	if (CircleSegmentMaxError == max_error)
		return;
	CircleSegmentMaxError = max_error;
	for (int i = 0; i < ARRAYSIZE(CircleSegmentCounts); i++)
	{
		const float radius = i + 1.0f;
		const int segment_count = IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_CALC(radius, CircleSegmentMaxError);
		CircleSegmentCounts[i] = (ImU8)ImMin(segment_count, 255);
	}
}

void ImDrawList::Clear()
{
	CmdBuffer.resize(0);
	IdxBuffer.resize(0);
	VtxBuffer.resize(0);
	Flags = _Data ? _Data->InitialFlags : ImDrawListFlags_None;
	_VtxCurrentOffset = 0;
	_VtxCurrentIdx = 0;
	_VtxWritePtr = NULL;
	_IdxWritePtr = NULL;
	_ClipRectStack.resize(0);
	_TextureIdStack.resize(0);
	_Path.resize(0);
	_Splitter.Clear();
}

void ImDrawList::ClearFreeMemory()
{
	CmdBuffer.clear();
	IdxBuffer.clear();
	VtxBuffer.clear();
	_VtxCurrentIdx = 0;
	_VtxWritePtr = NULL;
	_IdxWritePtr = NULL;
	_ClipRectStack.clear();
	_TextureIdStack.clear();
	_Path.clear();
	_Splitter.ClearFreeMemory();
}

ImDrawList* ImDrawList::CloneOutput() const
{
	ImDrawList* dst = IM_NEW(ImDrawList(_Data));
	dst->CmdBuffer = CmdBuffer;
	dst->IdxBuffer = IdxBuffer;
	dst->VtxBuffer = VtxBuffer;
	dst->Flags = Flags;
	return dst;
}

#define GetCurrentClipRect() (_ClipRectStack.Size ? _ClipRectStack.Data[_ClipRectStack.Size-1] : _Data->ClipRectFullscreen)

#define GetCurrentTextureId() (_TextureIdStack.Size ? _TextureIdStack.Data[_TextureIdStack.Size-1] : (ImTextureID)NULL)

void ImDrawList::AddDrawCmd()
{
	ImDrawCmd draw_cmd;
	draw_cmd.ClipRect = GetCurrentClipRect();
	draw_cmd.TextureId = GetCurrentTextureId();
	draw_cmd.VtxOffset = _VtxCurrentOffset;
	draw_cmd.IdxOffset = IdxBuffer.Size;

	CmdBuffer.push_back(draw_cmd);
}

void ImDrawList::AddCallback(ImDrawCallback callback, void* callback_data)
{
	ImDrawCmd* current_cmd = CmdBuffer.Size ? &CmdBuffer.back() : NULL;
	if (!current_cmd || current_cmd->ElemCount != 0 || current_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		current_cmd = &CmdBuffer.back();
	}
	current_cmd->UserCallback = callback;
	current_cmd->UserCallbackData = callback_data;

	AddDrawCmd(); // Force a new command after us (see comment below)
}

void ImDrawList::UpdateClipRect()
{
	// If current command is used with different settings we need to add a new command
	const ImVec4 curr_clip_rect = GetCurrentClipRect();
	ImDrawCmd* curr_cmd = CmdBuffer.Size > 0 ? &CmdBuffer.Data[CmdBuffer.Size - 1] : NULL;
	if (!curr_cmd || (curr_cmd->ElemCount != 0 && memcmp(&curr_cmd->ClipRect, &curr_clip_rect, sizeof(ImVec4)) != 0) || curr_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		return;
	}

	// Try to merge with previous command if it matches, else use current command
	ImDrawCmd* prev_cmd = CmdBuffer.Size > 1 ? curr_cmd - 1 : NULL;
	if (curr_cmd->ElemCount == 0 && prev_cmd && memcmp(&prev_cmd->ClipRect, &curr_clip_rect, sizeof(ImVec4)) == 0 && prev_cmd->TextureId == GetCurrentTextureId() && prev_cmd->UserCallback == NULL)
		CmdBuffer.pop_back();
	else
		curr_cmd->ClipRect = curr_clip_rect;
}

void ImDrawList::UpdateTextureID()
{
	// If current command is used with different settings we need to add a new command
	const ImTextureID curr_texture_id = GetCurrentTextureId();
	ImDrawCmd* curr_cmd = CmdBuffer.Size ? &CmdBuffer.back() : NULL;
	if (!curr_cmd || (curr_cmd->ElemCount != 0 && curr_cmd->TextureId != curr_texture_id) || curr_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		return;
	}

	// Try to merge with previous command if it matches, else use current command
	ImDrawCmd* prev_cmd = CmdBuffer.Size > 1 ? curr_cmd - 1 : NULL;
	if (curr_cmd->ElemCount == 0 && prev_cmd && prev_cmd->TextureId == curr_texture_id && memcmp(&prev_cmd->ClipRect, &GetCurrentClipRect(), sizeof(ImVec4)) == 0 && prev_cmd->UserCallback == NULL)
		CmdBuffer.pop_back();
	else
		curr_cmd->TextureId = curr_texture_id;
}

void ImDrawList::PushClipRect(ImVec2 cr_min, ImVec2 cr_max, bool intersect_with_current_clip_rect)
{
	ImVec4 cr(cr_min.x, cr_min.y, cr_max.x, cr_max.y);
	if (intersect_with_current_clip_rect && _ClipRectStack.Size)
	{
		ImVec4 current = _ClipRectStack.Data[_ClipRectStack.Size - 1];
		if (cr.x < current.x) cr.x = current.x;
		if (cr.y < current.y) cr.y = current.y;
		if (cr.z > current.z) cr.z = current.z;
		if (cr.w > current.w) cr.w = current.w;
	}
	cr.z = ImMax(cr.x, cr.z);
	cr.w = ImMax(cr.y, cr.w);

	_ClipRectStack.push_back(cr);
	UpdateClipRect();
}

void ImDrawList::PushClipRectFullScreen()
{
	PushClipRect(ImVec2(_Data->ClipRectFullscreen.x, _Data->ClipRectFullscreen.y), ImVec2(_Data->ClipRectFullscreen.z, _Data->ClipRectFullscreen.w));
}

void ImDrawList::PopClipRect()
{
	_ClipRectStack.pop_back();
	UpdateClipRect();
}

void ImDrawList::PushTextureID(ImTextureID texture_id)
{
	_TextureIdStack.push_back(texture_id);
	UpdateTextureID();
}

void ImDrawList::PopTextureID()
{
	_TextureIdStack.pop_back();
	UpdateTextureID();
}

void ImDrawList::PrimReserve(int idx_count, int vtx_count)
{
	// Large mesh support (when enabled)
	if (sizeof(ImDrawIdx) == 2 && (_VtxCurrentIdx + vtx_count >= (1 << 16)) && (Flags & ImDrawListFlags_AllowVtxOffset))
	{
		_VtxCurrentOffset = VtxBuffer.Size;
		_VtxCurrentIdx = 0;
		AddDrawCmd();
	}

	ImDrawCmd& draw_cmd = CmdBuffer.Data[CmdBuffer.Size - 1];
	draw_cmd.ElemCount += idx_count;

	int vtx_buffer_old_size = VtxBuffer.Size;
	VtxBuffer.resize(vtx_buffer_old_size + vtx_count);
	_VtxWritePtr = VtxBuffer.Data + vtx_buffer_old_size;

	int idx_buffer_old_size = IdxBuffer.Size;
	IdxBuffer.resize(idx_buffer_old_size + idx_count);
	_IdxWritePtr = IdxBuffer.Data + idx_buffer_old_size;
}

void ImDrawList::PrimUnreserve(int idx_count, int vtx_count)
{
	ImDrawCmd& draw_cmd = CmdBuffer.Data[CmdBuffer.Size - 1];
	draw_cmd.ElemCount -= idx_count;
	VtxBuffer.shrink(VtxBuffer.Size - vtx_count);
	IdxBuffer.shrink(IdxBuffer.Size - idx_count);
}

void ImDrawList::PrimRect(const ImVec2& a, const ImVec2& c, ImU32 col)
{
	ImVec2 b(c.x, a.y), d(a.x, c.y), uv(_Data->TexUvWhitePixel);
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

void ImDrawList::PrimRectUV(const ImVec2& a, const ImVec2& c, const ImVec2& uv_a, const ImVec2& uv_c, ImU32 col)
{
	ImVec2 b(c.x, a.y), d(a.x, c.y), uv_b(uv_c.x, uv_a.y), uv_d(uv_a.x, uv_c.y);
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv_a; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv_b; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv_c; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv_d; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

void ImDrawList::PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col)
{
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv_a; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv_b; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv_c; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv_d; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

#define IM_NORMALIZE2F_OVER_ZERO(VX,VY) do { float d2 = VX*VX + VY*VY; if (d2 > 0.0f) { float inv_len = 1.0f / ImSqrt(d2); VX *= inv_len; VY *= inv_len; } } while (0)

#define IM_FIXNORMAL2F(VX,VY) do { float d2 = VX*VX + VY*VY; if (d2 < 0.5f) d2 = 0.5f; float inv_lensq = 1.0f / d2; VX *= inv_lensq; VY *= inv_lensq; } while (0)

void ImDrawList::AddPolyline(const ImVec2* points, const int points_count, ImU32 col, bool closed, float thickness)
{
	if (points_count < 2)
		return;

	const ImVec2 uv = _Data->TexUvWhitePixel;

	int count = points_count;
	if (!closed)
		count = points_count - 1;

	const bool thick_line = thickness > 1.0f;
	if (Flags & ImDrawListFlags_AntiAliasedLines)
	{
		// Anti-aliased stroke
		const float AA_SIZE = 1.0f;
		const ImU32 col_trans = col & ~IM_COL32_A_MASK;

		const int idx_count = thick_line ? count * 18 : count * 12;
		const int vtx_count = thick_line ? points_count * 4 : points_count * 3;
		PrimReserve(idx_count, vtx_count);

		// Temporary buffer
		ImVec2* temp_normals = (ImVec2*)alloca(points_count * (thick_line ? 5 : 3) * sizeof(ImVec2)); //-V630
		ImVec2* temp_points = temp_normals + points_count;

		for (int i1 = 0; i1 < count; i1++)
		{
			const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
			float dx = points[i2].x - points[i1].x;
			float dy = points[i2].y - points[i1].y;
			IM_NORMALIZE2F_OVER_ZERO(dx, dy);
			temp_normals[i1].x = dy;
			temp_normals[i1].y = -dx;
		}
		if (!closed)
			temp_normals[points_count - 1] = temp_normals[points_count - 2];

		if (!thick_line)
		{
			if (!closed)
			{
				temp_points[0] = points[0] + temp_normals[0] * AA_SIZE;
				temp_points[1] = points[0] - temp_normals[0] * AA_SIZE;
				temp_points[(points_count - 1) * 2 + 0] = points[points_count - 1] + temp_normals[points_count - 1] * AA_SIZE;
				temp_points[(points_count - 1) * 2 + 1] = points[points_count - 1] - temp_normals[points_count - 1] * AA_SIZE;
			}

			// FIXME-OPT: Merge the different loops, possibly remove the temporary buffer.
			unsigned int idx1 = _VtxCurrentIdx;
			for (int i1 = 0; i1 < count; i1++)
			{
				const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
				unsigned int idx2 = (i1 + 1) == points_count ? _VtxCurrentIdx : idx1 + 3;

				// Average normals
				float dm_x = (temp_normals[i1].x + temp_normals[i2].x) * 0.5f;
				float dm_y = (temp_normals[i1].y + temp_normals[i2].y) * 0.5f;
				IM_FIXNORMAL2F(dm_x, dm_y);
				dm_x *= AA_SIZE;
				dm_y *= AA_SIZE;

				// Add temporary vertexes
				ImVec2* out_vtx = &temp_points[i2 * 2];
				out_vtx[0].x = points[i2].x + dm_x;
				out_vtx[0].y = points[i2].y + dm_y;
				out_vtx[1].x = points[i2].x - dm_x;
				out_vtx[1].y = points[i2].y - dm_y;

				// Add indexes
				_IdxWritePtr[0] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[1] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[2] = (ImDrawIdx)(idx1 + 2);
				_IdxWritePtr[3] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[4] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx2 + 0);
				_IdxWritePtr[6] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[7] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[8] = (ImDrawIdx)(idx1 + 0);
				_IdxWritePtr[9] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[10] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[11] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr += 12;

				idx1 = idx2;
			}

			// Add vertexes
			for (int i = 0; i < points_count; i++)
			{
				_VtxWritePtr[0].pos = points[i]; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
				_VtxWritePtr[1].pos = temp_points[i * 2 + 0]; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col_trans;
				_VtxWritePtr[2].pos = temp_points[i * 2 + 1]; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col_trans;
				_VtxWritePtr += 3;
			}
		}
		else
		{
			const float half_inner_thickness = (thickness - AA_SIZE) * 0.5f;
			if (!closed)
			{
				temp_points[0] = points[0] + temp_normals[0] * (half_inner_thickness + AA_SIZE);
				temp_points[1] = points[0] + temp_normals[0] * (half_inner_thickness);
				temp_points[2] = points[0] - temp_normals[0] * (half_inner_thickness);
				temp_points[3] = points[0] - temp_normals[0] * (half_inner_thickness + AA_SIZE);
				temp_points[(points_count - 1) * 4 + 0] = points[points_count - 1] + temp_normals[points_count - 1] * (half_inner_thickness + AA_SIZE);
				temp_points[(points_count - 1) * 4 + 1] = points[points_count - 1] + temp_normals[points_count - 1] * (half_inner_thickness);
				temp_points[(points_count - 1) * 4 + 2] = points[points_count - 1] - temp_normals[points_count - 1] * (half_inner_thickness);
				temp_points[(points_count - 1) * 4 + 3] = points[points_count - 1] - temp_normals[points_count - 1] * (half_inner_thickness + AA_SIZE);
			}

			// FIXME-OPT: Merge the different loops, possibly remove the temporary buffer.
			unsigned int idx1 = _VtxCurrentIdx;
			for (int i1 = 0; i1 < count; i1++)
			{
				const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
				unsigned int idx2 = (i1 + 1) == points_count ? _VtxCurrentIdx : idx1 + 4;

				// Average normals
				float dm_x = (temp_normals[i1].x + temp_normals[i2].x) * 0.5f;
				float dm_y = (temp_normals[i1].y + temp_normals[i2].y) * 0.5f;
				IM_FIXNORMAL2F(dm_x, dm_y);
				float dm_out_x = dm_x * (half_inner_thickness + AA_SIZE);
				float dm_out_y = dm_y * (half_inner_thickness + AA_SIZE);
				float dm_in_x = dm_x * half_inner_thickness;
				float dm_in_y = dm_y * half_inner_thickness;

				// Add temporary vertexes
				ImVec2* out_vtx = &temp_points[i2 * 4];
				out_vtx[0].x = points[i2].x + dm_out_x;
				out_vtx[0].y = points[i2].y + dm_out_y;
				out_vtx[1].x = points[i2].x + dm_in_x;
				out_vtx[1].y = points[i2].y + dm_in_y;
				out_vtx[2].x = points[i2].x - dm_in_x;
				out_vtx[2].y = points[i2].y - dm_in_y;
				out_vtx[3].x = points[i2].x - dm_out_x;
				out_vtx[3].y = points[i2].y - dm_out_y;

				// Add indexes
				_IdxWritePtr[0] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[1] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx1 + 2);
				_IdxWritePtr[3] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[4] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr[6] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[7] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[8] = (ImDrawIdx)(idx1 + 0);
				_IdxWritePtr[9] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[10] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[11] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr[12] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[13] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[14] = (ImDrawIdx)(idx1 + 3);
				_IdxWritePtr[15] = (ImDrawIdx)(idx1 + 3); _IdxWritePtr[16] = (ImDrawIdx)(idx2 + 3); _IdxWritePtr[17] = (ImDrawIdx)(idx2 + 2);
				_IdxWritePtr += 18;

				idx1 = idx2;
			}

			// Add vertexes
			for (int i = 0; i < points_count; i++)
			{
				_VtxWritePtr[0].pos = temp_points[i * 4 + 0]; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col_trans;
				_VtxWritePtr[1].pos = temp_points[i * 4 + 1]; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
				_VtxWritePtr[2].pos = temp_points[i * 4 + 2]; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
				_VtxWritePtr[3].pos = temp_points[i * 4 + 3]; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col_trans;
				_VtxWritePtr += 4;
			}
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
	else
	{
		// Non Anti-aliased Stroke
		const int idx_count = count * 6;
		const int vtx_count = count * 4; // FIXME-OPT: Not sharing edges
		PrimReserve(idx_count, vtx_count);

		for (int i1 = 0; i1 < count; i1++)
		{
			const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
			const ImVec2& p1 = points[i1];
			const ImVec2& p2 = points[i2];

			float dx = p2.x - p1.x;
			float dy = p2.y - p1.y;
			IM_NORMALIZE2F_OVER_ZERO(dx, dy);
			dx *= (thickness * 0.5f);
			dy *= (thickness * 0.5f);

			_VtxWritePtr[0].pos.x = p1.x + dy; _VtxWritePtr[0].pos.y = p1.y - dx; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
			_VtxWritePtr[1].pos.x = p2.x + dy; _VtxWritePtr[1].pos.y = p2.y - dx; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
			_VtxWritePtr[2].pos.x = p2.x - dy; _VtxWritePtr[2].pos.y = p2.y + dx; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
			_VtxWritePtr[3].pos.x = p1.x - dy; _VtxWritePtr[3].pos.y = p1.y + dx; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col;
			_VtxWritePtr += 4;

			_IdxWritePtr[0] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[1] = (ImDrawIdx)(_VtxCurrentIdx + 1); _IdxWritePtr[2] = (ImDrawIdx)(_VtxCurrentIdx + 2);
			_IdxWritePtr[3] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[4] = (ImDrawIdx)(_VtxCurrentIdx + 2); _IdxWritePtr[5] = (ImDrawIdx)(_VtxCurrentIdx + 3);
			_IdxWritePtr += 6;
			_VtxCurrentIdx += 4;
		}
	}
}

void ImDrawList::AddConvexPolyFilled(const ImVec2* points, const int points_count, ImU32 col)
{
	if (points_count < 3)
		return;

	const ImVec2 uv = _Data->TexUvWhitePixel;

	if (Flags & ImDrawListFlags_AntiAliasedFill)
	{
		// Anti-aliased Fill
		const float AA_SIZE = 1.0f;
		const ImU32 col_trans = col & ~IM_COL32_A_MASK;
		const int idx_count = (points_count - 2) * 3 + points_count * 6;
		const int vtx_count = (points_count * 2);
		PrimReserve(idx_count, vtx_count);

		// Add indexes for fill
		unsigned int vtx_inner_idx = _VtxCurrentIdx;
		unsigned int vtx_outer_idx = _VtxCurrentIdx + 1;
		for (int i = 2; i < points_count; i++)
		{
			_IdxWritePtr[0] = (ImDrawIdx)(vtx_inner_idx); _IdxWritePtr[1] = (ImDrawIdx)(vtx_inner_idx + ((i - 1) << 1)); _IdxWritePtr[2] = (ImDrawIdx)(vtx_inner_idx + (i << 1));
			_IdxWritePtr += 3;
		}

		// Compute normals
		ImVec2* temp_normals = (ImVec2*)alloca(points_count * sizeof(ImVec2)); //-V630
		for (int i0 = points_count - 1, i1 = 0; i1 < points_count; i0 = i1++)
		{
			const ImVec2& p0 = points[i0];
			const ImVec2& p1 = points[i1];
			float dx = p1.x - p0.x;
			float dy = p1.y - p0.y;
			IM_NORMALIZE2F_OVER_ZERO(dx, dy);
			temp_normals[i0].x = dy;
			temp_normals[i0].y = -dx;
		}

		for (int i0 = points_count - 1, i1 = 0; i1 < points_count; i0 = i1++)
		{
			// Average normals
			const ImVec2& n0 = temp_normals[i0];
			const ImVec2& n1 = temp_normals[i1];
			float dm_x = (n0.x + n1.x) * 0.5f;
			float dm_y = (n0.y + n1.y) * 0.5f;
			IM_FIXNORMAL2F(dm_x, dm_y);
			dm_x *= AA_SIZE * 0.5f;
			dm_y *= AA_SIZE * 0.5f;

			// Add vertices
			_VtxWritePtr[0].pos.x = (points[i1].x - dm_x); _VtxWritePtr[0].pos.y = (points[i1].y - dm_y); _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col; // Inner
			_VtxWritePtr[1].pos.x = (points[i1].x + dm_x); _VtxWritePtr[1].pos.y = (points[i1].y + dm_y); _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col_trans; // Outer
			_VtxWritePtr += 2;

			// Add indexes for fringes
			_IdxWritePtr[0] = (ImDrawIdx)(vtx_inner_idx + (i1 << 1)); _IdxWritePtr[1] = (ImDrawIdx)(vtx_inner_idx + (i0 << 1)); _IdxWritePtr[2] = (ImDrawIdx)(vtx_outer_idx + (i0 << 1));
			_IdxWritePtr[3] = (ImDrawIdx)(vtx_outer_idx + (i0 << 1)); _IdxWritePtr[4] = (ImDrawIdx)(vtx_outer_idx + (i1 << 1)); _IdxWritePtr[5] = (ImDrawIdx)(vtx_inner_idx + (i1 << 1));
			_IdxWritePtr += 6;
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
	else
	{
		// Non Anti-aliased Fill
		const int idx_count = (points_count - 2) * 3;
		const int vtx_count = points_count;
		PrimReserve(idx_count, vtx_count);
		for (int i = 0; i < vtx_count; i++)
		{
			_VtxWritePtr[0].pos = points[i]; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
			_VtxWritePtr++;
		}
		for (int i = 2; i < points_count; i++)
		{
			_IdxWritePtr[0] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[1] = (ImDrawIdx)(_VtxCurrentIdx + i - 1); _IdxWritePtr[2] = (ImDrawIdx)(_VtxCurrentIdx + i);
			_IdxWritePtr += 3;
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
}

void ImDrawList::PathArcToFast(const ImVec2& center, float radius, int a_min_of_12, int a_max_of_12)
{
	if (radius == 0.0f || a_min_of_12 > a_max_of_12)
	{
		_Path.push_back(center);
		return;
	}

	// For legacy reason the PathArcToFast() always takes angles where 2*PI is represented by 12,
	// but it is possible to set IM_DRAWLIST_ARCFAST_TESSELATION_MULTIPLIER to a higher value. This should compile to a no-op otherwise.
#if IM_DRAWLIST_ARCFAST_TESSELLATION_MULTIPLIER != 1
	a_min_of_12 *= IM_DRAWLIST_ARCFAST_TESSELLATION_MULTIPLIER;
	a_max_of_12 *= IM_DRAWLIST_ARCFAST_TESSELLATION_MULTIPLIER;
#endif

	_Path.reserve(_Path.Size + (a_max_of_12 - a_min_of_12 + 1));
	for (int a = a_min_of_12; a <= a_max_of_12; a++)
	{
		const ImVec2& c = _Data->ArcFastVtx[a % ARRAYSIZE(_Data->ArcFastVtx)];
		_Path.push_back(ImVec2(center.x + c.x * radius, center.y + c.y * radius));
	}
}

void ImDrawList::PathArcTo(const ImVec2& center, float radius, float a_min, float a_max, int num_segments)
{
	if (radius == 0.0f)
	{
		_Path.push_back(center);
		return;
	}

	// Note that we are adding a point at both a_min and a_max.
	// If you are trying to draw a full closed circle you don't want the overlapping points!
	_Path.reserve(_Path.Size + (num_segments + 1));
	for (int i = 0; i <= num_segments; i++)
	{
		const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
		_Path.push_back(ImVec2(center.x + ImCos(a) * radius, center.y + ImSin(a) * radius));
	}
}

ImVec2 ImBezierCalc(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, float t)
{
	float u = 1.0f - t;
	float w1 = u * u*u;
	float w2 = 3 * u*u*t;
	float w3 = 3 * u*t*t;
	float w4 = t * t*t;
	return ImVec2(w1*p1.x + w2 * p2.x + w3 * p3.x + w4 * p4.x, w1*p1.y + w2 * p2.y + w3 * p3.y + w4 * p4.y);
}

static void PathBezierToCasteljau(ImVector<ImVec2>* path, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float tess_tol, int level)
{
	float dx = x4 - x1;
	float dy = y4 - y1;
	float d2 = ((x2 - x4) * dy - (y2 - y4) * dx);
	float d3 = ((x3 - x4) * dy - (y3 - y4) * dx);
	d2 = (d2 >= 0) ? d2 : -d2;
	d3 = (d3 >= 0) ? d3 : -d3;
	if ((d2 + d3) * (d2 + d3) < tess_tol * (dx*dx + dy * dy))
	{
		path->push_back(ImVec2(x4, y4));
	}
	else if (level < 10)
	{
		float x12 = (x1 + x2)*0.5f, y12 = (y1 + y2)*0.5f;
		float x23 = (x2 + x3)*0.5f, y23 = (y2 + y3)*0.5f;
		float x34 = (x3 + x4)*0.5f, y34 = (y3 + y4)*0.5f;
		float x123 = (x12 + x23)*0.5f, y123 = (y12 + y23)*0.5f;
		float x234 = (x23 + x34)*0.5f, y234 = (y23 + y34)*0.5f;
		float x1234 = (x123 + x234)*0.5f, y1234 = (y123 + y234)*0.5f;
		PathBezierToCasteljau(path, x1, y1, x12, y12, x123, y123, x1234, y1234, tess_tol, level + 1);
		PathBezierToCasteljau(path, x1234, y1234, x234, y234, x34, y34, x4, y4, tess_tol, level + 1);
	}
}

void ImDrawList::PathBezierCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments)
{
	ImVec2 p1 = _Path.back();
	if (num_segments == 0)
	{
		PathBezierToCasteljau(&_Path, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, _Data->CurveTessellationTol, 0); // Auto-tessellated
	}
	else
	{
		float t_step = 1.0f / (float)num_segments;
		for (int i_step = 1; i_step <= num_segments; i_step++)
			_Path.push_back(ImBezierCalc(p1, p2, p3, p4, t_step * i_step));
	}
}

void ImDrawList::PathRect(const ImVec2& a, const ImVec2& b, float rounding, ImDrawCornerFlags rounding_corners)
{
	rounding = ImMin(rounding, ImFabs(b.x - a.x) * (((rounding_corners & ImDrawCornerFlags_Top) == ImDrawCornerFlags_Top) || ((rounding_corners & ImDrawCornerFlags_Bot) == ImDrawCornerFlags_Bot) ? 0.5f : 1.0f) - 1.0f);
	rounding = ImMin(rounding, ImFabs(b.y - a.y) * (((rounding_corners & ImDrawCornerFlags_Left) == ImDrawCornerFlags_Left) || ((rounding_corners & ImDrawCornerFlags_Right) == ImDrawCornerFlags_Right) ? 0.5f : 1.0f) - 1.0f);

	if (rounding <= 0.0f || rounding_corners == 0)
	{
		PathLineTo(a);
		PathLineTo(ImVec2(b.x, a.y));
		PathLineTo(b);
		PathLineTo(ImVec2(a.x, b.y));
	}
	else
	{
		const float rounding_tl = (rounding_corners & ImDrawCornerFlags_TopLeft) ? rounding : 0.0f;
		const float rounding_tr = (rounding_corners & ImDrawCornerFlags_TopRight) ? rounding : 0.0f;
		const float rounding_br = (rounding_corners & ImDrawCornerFlags_BotRight) ? rounding : 0.0f;
		const float rounding_bl = (rounding_corners & ImDrawCornerFlags_BotLeft) ? rounding : 0.0f;
		PathArcToFast(ImVec2(a.x + rounding_tl, a.y + rounding_tl), rounding_tl, 6, 9);
		PathArcToFast(ImVec2(b.x - rounding_tr, a.y + rounding_tr), rounding_tr, 9, 12);
		PathArcToFast(ImVec2(b.x - rounding_br, b.y - rounding_br), rounding_br, 0, 3);
		PathArcToFast(ImVec2(a.x + rounding_bl, b.y - rounding_bl), rounding_bl, 3, 6);
	}
}

void ImDrawList::AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	PathLineTo(p1 + ImVec2(0.5f, 0.5f));
	PathLineTo(p2 + ImVec2(0.5f, 0.5f));
	PathStroke(col, false, thickness);
}

void ImDrawList::AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding, ImDrawCornerFlags rounding_corners, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	if (Flags & ImDrawListFlags_AntiAliasedLines)
		PathRect(p_min + ImVec2(0.50f, 0.50f), p_max - ImVec2(0.50f, 0.50f), rounding, rounding_corners);
	else
		PathRect(p_min + ImVec2(0.50f, 0.50f), p_max - ImVec2(0.49f, 0.49f), rounding, rounding_corners); // Better looking lower-right corner and rounded non-AA shapes.
	PathStroke(col, true, thickness);
}

void ImDrawList::AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding, ImDrawCornerFlags rounding_corners)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	if (rounding > 0.0f)
	{
		PathRect(p_min, p_max, rounding, rounding_corners);
		PathFillConvex(col);
	}
	else
	{
		PrimReserve(6, 4);
		PrimRect(p_min, p_max, col);
	}
}

void ImDrawList::AddRectFilledMultiColor(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left)
{
	if (((col_upr_left | col_upr_right | col_bot_right | col_bot_left) & IM_COL32_A_MASK) == 0)
		return;

	const ImVec2 uv = _Data->TexUvWhitePixel;
	PrimReserve(6, 4);
	PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 1)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 2));
	PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 2)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 3));
	PrimWriteVtx(p_min, uv, col_upr_left);
	PrimWriteVtx(ImVec2(p_max.x, p_min.y), uv, col_upr_right);
	PrimWriteVtx(p_max, uv, col_bot_right);
	PrimWriteVtx(ImVec2(p_min.x, p_max.y), uv, col_bot_left);
}

void ImDrawList::AddQuad(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(p1);
	PathLineTo(p2);
	PathLineTo(p3);
	PathLineTo(p4);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddQuadFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(p1);
	PathLineTo(p2);
	PathLineTo(p3);
	PathLineTo(p4);
	PathFillConvex(col);
}

void ImDrawList::AddTriangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(p1);
	PathLineTo(p2);
	PathLineTo(p3);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(p1);
	PathLineTo(p2);
	PathLineTo(p3);
	PathFillConvex(col);
}

/*
void ImDrawList::AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0 || radius <= 0.0f)
		return;

	// Obtain segment count
	if (num_segments <= 0)
	{
		// Automatic segment count
		const int radius_idx = (int)radius - 1;
		if (radius_idx < ARRAYSIZE(_Data->CircleSegmentCounts))
			num_segments = _Data->CircleSegmentCounts[radius_idx]; // Use cached value
		else
			num_segments = IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_CALC(radius, _Data->CircleSegmentMaxError);
	}
	else
	{
		// Explicit segment count (still clamp to avoid drawing insanely tessellated shapes)
		num_segments = ImClamp(num_segments, 3, IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_MAX);
	}

	// Because we are filling a closed shape we remove 1 from the count of segments/points
	const float a_max = (3.1415926f * 2.0f) * ((float)num_segments - 1.0f) / (float)num_segments;
	if (num_segments == 12)
		PathArcToFast(center, radius - 0.5f, 0, 12);
	else
		PathArcTo(center, radius - 0.5f, 0.0f, a_max, num_segments - 1);
	PathStroke(col, true, thickness);
}
*/

void ImDrawList::AddCircle(const ImVec2& centre, float radius, ImU32 col, int num_segments, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0 || num_segments <= 2)
		return;

	// Because we are filling a closed shape we remove 1 from the count of segments/points
	const float a_max = 3.1415926f * 2.0f * ((float)num_segments - 1.0f) / (float)num_segments;
	PathArcTo(centre, radius - 0.5f, 0.0f, a_max, num_segments - 1);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments)
{
	if ((col & IM_COL32_A_MASK) == 0 || radius <= 0.0f)
		return;

	// Obtain segment count
	if (num_segments <= 0)
	{
		// Automatic segment count
		const int radius_idx = (int)radius - 1;
		if (radius_idx < ARRAYSIZE(_Data->CircleSegmentCounts))
			num_segments = _Data->CircleSegmentCounts[radius_idx]; // Use cached value
		else
			num_segments = IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_CALC(radius, _Data->CircleSegmentMaxError);
	}
	else
	{
		// Explicit segment count (still clamp to avoid drawing insanely tessellated shapes)
		num_segments = ImClamp(num_segments, 3, IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_MAX);
	}

	// Because we are filling a closed shape we remove 1 from the count of segments/points
	const float a_max = (3.1415926f * 2.0f) * ((float)num_segments - 1.0f) / (float)num_segments;
	if (num_segments == 12)
		PathArcToFast(center, radius, 0, 12);
	else
		PathArcTo(center, radius, 0.0f, a_max, num_segments - 1);
	PathFillConvex(col);
}

void ImDrawList::AddNgon(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0 || num_segments <= 2)
		return;

	// Because we are filling a closed shape we remove 1 from the count of segments/points
	const float a_max = (3.1415926f * 2.0f) * ((float)num_segments - 1.0f) / (float)num_segments;
	PathArcTo(center, radius - 0.5f, 0.0f, a_max, num_segments - 1);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddNgonFilled(const ImVec2& center, float radius, ImU32 col, int num_segments)
{
	if ((col & IM_COL32_A_MASK) == 0 || num_segments <= 2)
		return;

	// Because we are filling a closed shape we remove 1 from the count of segments/points
	const float a_max = (3.1415926f * 2.0f) * ((float)num_segments - 1.0f) / (float)num_segments;
	PathArcTo(center, radius, 0.0f, a_max, num_segments - 1);
	PathFillConvex(col);
}

void ImDrawList::AddBezierCurve(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(p1);
	PathBezierCurveTo(p2, p3, p4, num_segments);
	PathStroke(col, false, thickness);
}

void ImDrawList::AddTextEx(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	if (text_end == NULL)
		text_end = text_begin + strlen(text_begin);

	if (text_begin == text_end)
		return;

	if (font == NULL)
		font = _Data->Font;

	if (font_size == 0.0f)
		font_size = _Data->FontSize;

	ImVec4 clip_rect = _ClipRectStack.back();

	if (cpu_fine_clip_rect)
	{
		clip_rect.x = ImMax(clip_rect.x, cpu_fine_clip_rect->x);
		clip_rect.y = ImMax(clip_rect.y, cpu_fine_clip_rect->y);
		clip_rect.z = ImMin(clip_rect.z, cpu_fine_clip_rect->z);
		clip_rect.w = ImMin(clip_rect.w, cpu_fine_clip_rect->w);
	}

	ImU32 BgColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.05f, 0.05f, 0.05f, 0.75f));

	font->RenderText(this, font_size, ImVec2(pos.x - 1, pos.y), BgColor, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
	font->RenderText(this, font_size, ImVec2(pos.x, pos.y - 1), BgColor, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
	font->RenderText(this, font_size, ImVec2(pos.x + 1, pos.y), BgColor, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
	font->RenderText(this, font_size, ImVec2(pos.x, pos.y + 1), BgColor, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
	font->RenderText(this, font_size, pos, col, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
}

void ImDrawList::AddTextEx(const ImVec2& pos, float font_size, ImU32 col, const char* text_begin, const char* text_end)
{
	AddTextEx(NULL, font_size, pos, col, text_begin, text_end);
}

void ImDrawList::AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	if (text_end == NULL)

		text_end = text_begin + strlen(text_begin);
	if (text_begin == text_end)
		return;

	if (font == NULL)
		font = _Data->Font;

	if (font_size == 0.0f)
		font_size = _Data->FontSize;

	ImVec4 clip_rect = _ClipRectStack.back();

	if (cpu_fine_clip_rect)
	{
		clip_rect.x = ImMax(clip_rect.x, cpu_fine_clip_rect->x);
		clip_rect.y = ImMax(clip_rect.y, cpu_fine_clip_rect->y);
		clip_rect.z = ImMin(clip_rect.z, cpu_fine_clip_rect->z);
		clip_rect.w = ImMin(clip_rect.w, cpu_fine_clip_rect->w);
	}

	font->RenderText(this, font_size, pos, col, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
}

void ImDrawList::AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end)
{
	AddText(NULL, 0.0f, pos, col, text_begin, text_end);
}

void ImDrawList::AddText(const ImVec2& pos, float font_size, ImU32 col, const char* text_begin, const char* text_end)
{
	AddText(NULL, font_size, pos, col, text_begin, text_end);
}

void ImDrawList::AddImage(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	const bool push_texture_id = _TextureIdStack.empty() || user_texture_id != _TextureIdStack.back();
	if (push_texture_id)
		PushTextureID(user_texture_id);

	PrimReserve(6, 4);
	PrimRectUV(p_min, p_max, uv_min, uv_max, col);

	if (push_texture_id)
		PopTextureID();
}

void ImDrawList::AddImageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1, const ImVec2& uv2, const ImVec2& uv3, const ImVec2& uv4, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	const bool push_texture_id = _TextureIdStack.empty() || user_texture_id != _TextureIdStack.back();
	if (push_texture_id)
		PushTextureID(user_texture_id);

	PrimReserve(6, 4);
	PrimQuadUV(p1, p2, p3, p4, uv1, uv2, uv3, uv4, col);

	if (push_texture_id)
		PopTextureID();
}

void ImDrawList::AddImageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding, ImDrawCornerFlags rounding_corners)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	if (rounding <= 0.0f || (rounding_corners & ImDrawCornerFlags_All) == 0)
	{
		AddImage(user_texture_id, p_min, p_max, uv_min, uv_max, col);
		return;
	}

	const bool push_texture_id = _TextureIdStack.empty() || user_texture_id != _TextureIdStack.back();
	if (push_texture_id)
		PushTextureID(user_texture_id);

	int vert_start_idx = VtxBuffer.Size;
	PathRect(p_min, p_max, rounding, rounding_corners);
	PathFillConvex(col);
	int vert_end_idx = VtxBuffer.Size;
	ImGui::ShadeVertsLinearUV(this, vert_start_idx, vert_end_idx, p_min, p_max, uv_min, uv_max, true);

	if (push_texture_id)
		PopTextureID();
}

void ImDrawListSplitter::ClearFreeMemory()
{
	for (int i = 0; i < _Channels.Size; i++)
	{
		if (i == _Current)
			memset(&_Channels[i], 0, sizeof(_Channels[i])); // Current channel is a copy of CmdBuffer/IdxBuffer, don't destruct again
		_Channels[i]._CmdBuffer.clear();
		_Channels[i]._IdxBuffer.clear();
	}
	_Current = 0;
	_Count = 1;
	_Channels.clear();
}

void ImDrawListSplitter::Split(ImDrawList* draw_list, int channels_count)
{
	int old_channels_count = _Channels.Size;
	if (old_channels_count < channels_count)
		_Channels.resize(channels_count);
	_Count = channels_count;

	// Channels[] (24/32 bytes each) hold storage that we'll swap with draw_list->_CmdBuffer/_IdxBuffer
	// The content of Channels[0] at this point doesn't matter. We clear it to make state tidy in a debugger but we don't strictly need to.
	// When we switch to the next channel, we'll copy draw_list->_CmdBuffer/_IdxBuffer into Channels[0] and then Channels[1] into draw_list->CmdBuffer/_IdxBuffer
	memset(&_Channels[0], 0, sizeof(ImDrawChannel));
	for (int i = 1; i < channels_count; i++)
	{
		if (i >= old_channels_count)
		{
			IM_PLACEMENT_NEW(&_Channels[i]) ImDrawChannel();
		}
		else
		{
			_Channels[i]._CmdBuffer.resize(0);
			_Channels[i]._IdxBuffer.resize(0);
		}
		if (_Channels[i]._CmdBuffer.Size == 0)
		{
			ImDrawCmd draw_cmd;
			draw_cmd.ClipRect = draw_list->_ClipRectStack.back();
			draw_cmd.TextureId = draw_list->_TextureIdStack.back();
			_Channels[i]._CmdBuffer.push_back(draw_cmd);
		}
	}
}

static inline bool CanMergeDrawCommands(ImDrawCmd* a, ImDrawCmd* b)
{
	return memcmp(&a->ClipRect, &b->ClipRect, sizeof(a->ClipRect)) == 0 && a->TextureId == b->TextureId && a->VtxOffset == b->VtxOffset && !a->UserCallback && !b->UserCallback;
}

void ImDrawListSplitter::Merge(ImDrawList* draw_list)
{
	// Note that we never use or rely on channels.Size because it is merely a buffer that we never shrink back to 0 to keep all sub-buffers ready for use.
	if (_Count <= 1)
		return;

	SetCurrentChannel(draw_list, 0);
	if (draw_list->CmdBuffer.Size != 0 && draw_list->CmdBuffer.back().ElemCount == 0)
		draw_list->CmdBuffer.pop_back();

	// Calculate our final buffer sizes. Also fix the incorrect IdxOffset values in each command.
	int new_cmd_buffer_count = 0;
	int new_idx_buffer_count = 0;
	ImDrawCmd* last_cmd = (_Count > 0 && draw_list->CmdBuffer.Size > 0) ? &draw_list->CmdBuffer.back() : NULL;
	int idx_offset = last_cmd ? last_cmd->IdxOffset + last_cmd->ElemCount : 0;
	for (int i = 1; i < _Count; i++)
	{
		ImDrawChannel& ch = _Channels[i];
		if (ch._CmdBuffer.Size > 0 && ch._CmdBuffer.back().ElemCount == 0)
			ch._CmdBuffer.pop_back();
		if (ch._CmdBuffer.Size > 0 && last_cmd != NULL && CanMergeDrawCommands(last_cmd, &ch._CmdBuffer[0]))
		{
			// Merge previous channel last draw command with current channel first draw command if matching.
			last_cmd->ElemCount += ch._CmdBuffer[0].ElemCount;
			idx_offset += ch._CmdBuffer[0].ElemCount;
			ch._CmdBuffer.erase(ch._CmdBuffer.Data); // FIXME-OPT: Improve for multiple merges.
		}
		if (ch._CmdBuffer.Size > 0)
			last_cmd = &ch._CmdBuffer.back();
		new_cmd_buffer_count += ch._CmdBuffer.Size;
		new_idx_buffer_count += ch._IdxBuffer.Size;
		for (int cmd_n = 0; cmd_n < ch._CmdBuffer.Size; cmd_n++)
		{
			ch._CmdBuffer.Data[cmd_n].IdxOffset = idx_offset;
			idx_offset += ch._CmdBuffer.Data[cmd_n].ElemCount;
		}
	}
	draw_list->CmdBuffer.resize(draw_list->CmdBuffer.Size + new_cmd_buffer_count);
	draw_list->IdxBuffer.resize(draw_list->IdxBuffer.Size + new_idx_buffer_count);

	// Write commands and indices in order (they are fairly small structures, we don't copy vertices only indices)
	ImDrawCmd* cmd_write = draw_list->CmdBuffer.Data + draw_list->CmdBuffer.Size - new_cmd_buffer_count;
	ImDrawIdx* idx_write = draw_list->IdxBuffer.Data + draw_list->IdxBuffer.Size - new_idx_buffer_count;
	for (int i = 1; i < _Count; i++)
	{
		ImDrawChannel& ch = _Channels[i];
		if (int sz = ch._CmdBuffer.Size) { memcpy(cmd_write, ch._CmdBuffer.Data, sz * sizeof(ImDrawCmd)); cmd_write += sz; }
		if (int sz = ch._IdxBuffer.Size) { memcpy(idx_write, ch._IdxBuffer.Data, sz * sizeof(ImDrawIdx)); idx_write += sz; }
	}
	draw_list->_IdxWritePtr = idx_write;
	draw_list->UpdateClipRect(); // We call this instead of AddDrawCmd(), so that empty channels won't produce an extra draw call.
	draw_list->UpdateTextureID();
	_Count = 1;
}

void ImDrawListSplitter::SetCurrentChannel(ImDrawList* draw_list, int idx)
{
	if (_Current == idx)
		return;
	// Overwrite ImVector (12/16 bytes), four times. This is merely a silly optimization instead of doing .swap()
	memcpy(&_Channels.Data[_Current]._CmdBuffer, &draw_list->CmdBuffer, sizeof(draw_list->CmdBuffer));
	memcpy(&_Channels.Data[_Current]._IdxBuffer, &draw_list->IdxBuffer, sizeof(draw_list->IdxBuffer));
	_Current = idx;
	memcpy(&draw_list->CmdBuffer, &_Channels.Data[idx]._CmdBuffer, sizeof(draw_list->CmdBuffer));
	memcpy(&draw_list->IdxBuffer, &_Channels.Data[idx]._IdxBuffer, sizeof(draw_list->IdxBuffer));
	draw_list->_IdxWritePtr = draw_list->IdxBuffer.Data + draw_list->IdxBuffer.Size;
}

void ImDrawData::DeIndexAllBuffers()
{
	ImVector<ImDrawVert> new_vtx_buffer;
	TotalVtxCount = TotalIdxCount = 0;
	for (int i = 0; i < CmdListsCount; i++)
	{
		ImDrawList* cmd_list = CmdLists[i];
		if (cmd_list->IdxBuffer.empty())
			continue;
		new_vtx_buffer.resize(cmd_list->IdxBuffer.Size);
		for (int j = 0; j < cmd_list->IdxBuffer.Size; j++)
			new_vtx_buffer[j] = cmd_list->VtxBuffer[cmd_list->IdxBuffer[j]];
		cmd_list->VtxBuffer.swap(new_vtx_buffer);
		cmd_list->IdxBuffer.resize(0);
		TotalVtxCount += cmd_list->VtxBuffer.Size;
	}
}

void ImDrawData::ScaleClipRects(const ImVec2& fb_scale)
{
	for (int i = 0; i < CmdListsCount; i++)
	{
		ImDrawList* cmd_list = CmdLists[i];
		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			ImDrawCmd* cmd = &cmd_list->CmdBuffer[cmd_i];
			cmd->ClipRect = ImVec4(cmd->ClipRect.x * fb_scale.x, cmd->ClipRect.y * fb_scale.y, cmd->ClipRect.z * fb_scale.x, cmd->ClipRect.w * fb_scale.y);
		}
	}
}

void ImGui::ShadeVertsLinearColorGradientKeepAlpha(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, ImVec2 gradient_p0, ImVec2 gradient_p1, ImU32 col0, ImU32 col1)
{
	ImVec2 gradient_extent = gradient_p1 - gradient_p0;
	float gradient_inv_length2 = 1.0f / ImLengthSqr(gradient_extent);
	ImDrawVert* vert_start = draw_list->VtxBuffer.Data + vert_start_idx;
	ImDrawVert* vert_end = draw_list->VtxBuffer.Data + vert_end_idx;
	for (ImDrawVert* vert = vert_start; vert < vert_end; vert++)
	{
		float d = ImDot(vert->pos - gradient_p0, gradient_extent);
		float t = ImClamp(d * gradient_inv_length2, 0.0f, 1.0f);
		int r = ImLerp((int)(col0 >> IM_COL32_R_SHIFT) & 0xFF, (int)(col1 >> IM_COL32_R_SHIFT) & 0xFF, t);
		int g = ImLerp((int)(col0 >> IM_COL32_G_SHIFT) & 0xFF, (int)(col1 >> IM_COL32_G_SHIFT) & 0xFF, t);
		int b = ImLerp((int)(col0 >> IM_COL32_B_SHIFT) & 0xFF, (int)(col1 >> IM_COL32_B_SHIFT) & 0xFF, t);
		vert->col = (r << IM_COL32_R_SHIFT) | (g << IM_COL32_G_SHIFT) | (b << IM_COL32_B_SHIFT) | (vert->col & IM_COL32_A_MASK);
	}
}

void ImGui::ShadeVertsLinearUV(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, bool clamp)
{
	const ImVec2 size = b - a;
	const ImVec2 uv_size = uv_b - uv_a;
	const ImVec2 scale = ImVec2(
		size.x != 0.0f ? (uv_size.x / size.x) : 0.0f,
		size.y != 0.0f ? (uv_size.y / size.y) : 0.0f);

	ImDrawVert* vert_start = draw_list->VtxBuffer.Data + vert_start_idx;
	ImDrawVert* vert_end = draw_list->VtxBuffer.Data + vert_end_idx;
	if (clamp)
	{
		const ImVec2 min = ImMin(uv_a, uv_b);
		const ImVec2 max = ImMax(uv_a, uv_b);
		for (ImDrawVert* vertex = vert_start; vertex < vert_end; ++vertex)
			vertex->uv = ImClamp(uv_a + ImMul(ImVec2(vertex->pos.x, vertex->pos.y) - a, scale), min, max);
	}
	else
	{
		for (ImDrawVert* vertex = vert_start; vertex < vert_end; ++vertex)
			vertex->uv = uv_a + ImMul(ImVec2(vertex->pos.x, vertex->pos.y) - a, scale);
	}
}

ImFontConfig::ImFontConfig()
{
	FontData = NULL;
	FontDataSize = 0;
	FontDataOwnedByAtlas = true;
	FontNo = 0;
	SizePixels = 0.0f;
	OversampleH = 3; // FIXME: 2 may be a better default?
	OversampleV = 1;
	PixelSnapH = false;
	GlyphExtraSpacing = ImVec2(0.0f, 0.0f);
	GlyphOffset = ImVec2(0.0f, 0.0f);
	GlyphRanges = NULL;
	GlyphMinAdvanceX = 0.0f;
	GlyphMaxAdvanceX = FLT_MAX;
	MergeMode = false;
	RasterizerFlags = 0x00;
	RasterizerMultiply = 1.0f;
	EllipsisChar = (ImWchar)-1;
	memset(Name, 0, sizeof(Name));
	DstFont = NULL;
}

const int FONT_ATLAS_DEFAULT_TEX_DATA_W_HALF = 108;

const int FONT_ATLAS_DEFAULT_TEX_DATA_H = 27;

const unsigned int FONT_ATLAS_DEFAULT_TEX_DATA_ID = 0x80000000;

static const char FONT_ATLAS_DEFAULT_TEX_DATA_PIXELS[FONT_ATLAS_DEFAULT_TEX_DATA_W_HALF * FONT_ATLAS_DEFAULT_TEX_DATA_H + 1] = {
 "..- -XXXXXXX- X - X -XXXXXXX - XXXXXXX- XX "
 "..- -X.....X- X.X - X.X -X.....X - X.....X- X..X "
 "--- -XXX.XXX- X...X - X...X -X....X - X....X- X..X "
 "X - X.X - X.....X - X.....X -X...X - X...X- X..X "
 "XX - X.X -X.......X- X.......X -X..X.X - X.X..X- X..X "
 "X.X - X.X -XXXX.XXXX- XXXX.XXXX -X.X X.X - X.X X.X- X..XXX "
 "X..X - X.X - X.X - X.X -XX X.X - X.X XX- X..X..XXX "
 "X...X - X.X - X.X - XX X.X XX - X.X - X.X - X..X..X..XX "
 "X....X - X.X - X.X - X.X X.X X.X - X.X - X.X - X..X..X..X.X "
 "X.....X - X.X - X.X - X..X X.X X..X - X.X - X.X -XXX X..X..X..X..X"
 "X......X - X.X - X.X - X...XXXXXX.XXXXXX...X - X.X XX-XX X.X -X..XX........X..X"
 "X.......X - X.X - X.X -X.....................X- X.X X.X-X.X X.X -X...X...........X"
 "X........X - X.X - X.X - X...XXXXXX.XXXXXX...X - X.X..X-X..X.X - X..............X"
 "X.........X -XXX.XXX- X.X - X..X X.X X..X - X...X-X...X - X.............X"
 "X..........X-X.....X- X.X - X.X X.X X.X - X....X-X....X - X.............X"
 "X......XXXXX-XXXXXXX- X.X - XX X.X XX - X.....X-X.....X - X............X"
 "X...X..X --------- X.X - X.X - XXXXXXX-XXXXXXX - X...........X "
 "X..X X..X - -XXXX.XXXX- XXXX.XXXX ------------------------------------- X..........X "
 "X.X X..X - -X.......X- X.......X - XX XX - - X..........X "
 "XX X..X - - X.....X - X.....X - X.X X.X - - X........X "
 " X..X - X...X - X...X - X..X X..X - - X........X "
 " XX - X.X - X.X - X...XXXXXXXXXXXXX...X - - XXXXXXXXXX "
 "------------ - X - X -X.....................X- ------------------"
 " ----------------------------------- X...XXXXXXXXXXXXX...X - "
 " - X..X X..X - "
 " - X.X X.X - "
 " - XX XX - "
};

static const ImVec2 FONT_ATLAS_DEFAULT_TEX_CURSOR_DATA[ImGuiMouseCursor_COUNT][3] = {
	{ ImVec2(0,3), ImVec2(12,19), ImVec2(0, 0) }, // ImGuiMouseCursor_Arrow
	{ ImVec2(13,0), ImVec2(7,16), ImVec2(1, 8) }, // ImGuiMouseCursor_TextInput
	{ ImVec2(31,0), ImVec2(23,23), ImVec2(11,11) }, // ImGuiMouseCursor_ResizeAll
	{ ImVec2(21,0), ImVec2(9,23), ImVec2(4,11) }, // ImGuiMouseCursor_ResizeNS
	{ ImVec2(55,18),ImVec2(23, 9), ImVec2(11, 4) }, // ImGuiMouseCursor_ResizeEW
	{ ImVec2(73,0), ImVec2(17,17), ImVec2(8, 8) }, // ImGuiMouseCursor_ResizeNESW
	{ ImVec2(55,0), ImVec2(17,17), ImVec2(8, 8) }, // ImGuiMouseCursor_ResizeNWSE
	{ ImVec2(91,0), ImVec2(17,22), ImVec2(5, 0) }, // ImGuiMouseCursor_Hand
};

ImFontAtlas::ImFontAtlas()
{
	Locked = false;
	Flags = ImFontAtlasFlags_None;
	TexID = (ImTextureID)NULL;
	TexDesiredWidth = 0;
	TexGlyphPadding = 1;

	TexPixelsAlpha8 = NULL;
	TexPixelsRGBA32 = NULL;
	TexWidth = TexHeight = 0;
	TexUvScale = ImVec2(0.0f, 0.0f);
	TexUvWhitePixel = ImVec2(0.0f, 0.0f);
	for (int n = 0; n < ARRAYSIZE(CustomRectIds); n++)
		CustomRectIds[n] = -1;
}

ImFontAtlas::~ImFontAtlas()
{
	Clear();
}

void ImFontAtlas::ClearInputData()
{
	for (int i = 0; i < ConfigData.Size; i++)
		if (ConfigData[i].FontData && ConfigData[i].FontDataOwnedByAtlas)
		{
			ImGui::MemFree(ConfigData[i].FontData);
			ConfigData[i].FontData = NULL;
		}

	// When clearing this we lose access to the font name and other information used to build the font.
	for (int i = 0; i < Fonts.Size; i++)
		if (Fonts[i]->ConfigData >= ConfigData.Data && Fonts[i]->ConfigData < ConfigData.Data + ConfigData.Size)
		{
			Fonts[i]->ConfigData = NULL;
			Fonts[i]->ConfigDataCount = 0;
		}
	ConfigData.clear();
	CustomRects.clear();
	for (int n = 0; n < ARRAYSIZE(CustomRectIds); n++)
		CustomRectIds[n] = -1;
}

void ImFontAtlas::ClearTexData()
{
	if (TexPixelsAlpha8)
		ImGui::MemFree(TexPixelsAlpha8);
	if (TexPixelsRGBA32)
		ImGui::MemFree(TexPixelsRGBA32);
	TexPixelsAlpha8 = NULL;
	TexPixelsRGBA32 = NULL;
}

void ImFontAtlas::ClearFonts()
{
	for (int i = 0; i < Fonts.Size; i++)
		IM_DELETE(Fonts[i]);
	Fonts.clear();
}

void ImFontAtlas::Clear()
{
	ClearInputData();
	ClearTexData();
	ClearFonts();
}

void ImFontAtlas::GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	// Build atlas on demand
	if (TexPixelsAlpha8 == NULL)
	{
		if (ConfigData.empty())
		{
			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttf", 15.f, NULL, io.Fonts->GetGlyphRangesChineseFull());
		}
		Build();
	}

	*out_pixels = TexPixelsAlpha8;
	if (out_width) *out_width = TexWidth;
	if (out_height) *out_height = TexHeight;
	if (out_bytes_per_pixel) *out_bytes_per_pixel = 1;
}

void ImFontAtlas::GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	// Convert to RGBA32 format on demand
	// Although it is likely to be the most commonly used format, our font rendering is 1 channel / 8 bpp
	if (!TexPixelsRGBA32)
	{
		unsigned char* pixels = NULL;
		GetTexDataAsAlpha8(&pixels, NULL, NULL);
		if (pixels)
		{
			TexPixelsRGBA32 = (unsigned int*)ImGui::MemAlloc((size_t)TexWidth * (size_t)TexHeight * 4);
			const unsigned char* src = pixels;
			unsigned int* dst = TexPixelsRGBA32;
			for (int n = TexWidth * TexHeight; n > 0; n--)
				*dst++ = IM_COL32(255, 255, 255, (unsigned int)(*src++));
		}
	}

	*out_pixels = (unsigned char*)TexPixelsRGBA32;
	if (out_width) *out_width = TexWidth;
	if (out_height) *out_height = TexHeight;
	if (out_bytes_per_pixel) *out_bytes_per_pixel = 4;
}

ImFont* ImFontAtlas::AddFont(const ImFontConfig* font_cfg)
{
	// Create new font
	if (!font_cfg->MergeMode)
		Fonts.push_back(IM_NEW(ImFont));

	ConfigData.push_back(*font_cfg);
	ImFontConfig& new_font_cfg = ConfigData.back();
	if (new_font_cfg.DstFont == NULL)
		new_font_cfg.DstFont = Fonts.back();
	if (!new_font_cfg.FontDataOwnedByAtlas)
	{
		new_font_cfg.FontData = ImGui::MemAlloc(new_font_cfg.FontDataSize);
		new_font_cfg.FontDataOwnedByAtlas = true;
		memcpy(new_font_cfg.FontData, font_cfg->FontData, (size_t)new_font_cfg.FontDataSize);
	}

	if (new_font_cfg.DstFont->EllipsisChar == (ImWchar)-1)
		new_font_cfg.DstFont->EllipsisChar = font_cfg->EllipsisChar;

	// Invalidate texture
	ClearTexData();
	return new_font_cfg.DstFont;
}

static unsigned int stb_decompress_length(const unsigned char *input);

static unsigned int stb_decompress(unsigned char *output, const unsigned char *input, unsigned int length);

static unsigned int Decode85Byte(char c) { return c >= '\\' ? c - 36 : c - 35; }

static void Decode85(const unsigned char* src, unsigned char* dst)
{
	while (*src)
	{
		unsigned int tmp = Decode85Byte(src[0]) + 85 * (Decode85Byte(src[1]) + 85 * (Decode85Byte(src[2]) + 85 * (Decode85Byte(src[3]) + 85 * Decode85Byte(src[4]))));
		dst[0] = ((tmp >> 0) & 0xFF); dst[1] = ((tmp >> 8) & 0xFF); dst[2] = ((tmp >> 16) & 0xFF); dst[3] = ((tmp >> 24) & 0xFF); // We can't assume little-endianness.
		src += 5;
		dst += 4;
	}
}

ImFont* ImFontAtlas::AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg_template, const ImWchar* glyph_ranges)
{
	size_t data_size = 0;
	void* data = ImFileLoadToMemory(filename, "rb", &data_size, 0);
	if (!data)
		data = ImFileLoadToMemory("C:\\Windows\\Fonts\\msyh.ttc", "rb", &data_size, 0);
	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	if (font_cfg.Name[0] == '\0')
	{
		// Store a short copy of filename into into the font name for convenience
		const char* p;
		for (p = filename + strlen(filename); p > filename && p[-1] != '/' && p[-1] != '\\'; p--) {}
		ImFormatString(font_cfg.Name, ARRAYSIZE(font_cfg.Name), "%s, %.0fpx", p, size_pixels);
	}
	return AddFontFromMemoryTTF(data, (int)data_size, size_pixels, &font_cfg, glyph_ranges);
}

ImFont* ImFontAtlas::AddFontFromMemoryTTF(void* ttf_data, int ttf_size, float size_pixels, const ImFontConfig* font_cfg_template, const ImWchar* glyph_ranges)
{
	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	font_cfg.FontData = ttf_data;
	font_cfg.FontDataSize = ttf_size;
	font_cfg.SizePixels = size_pixels;
	if (glyph_ranges)
		font_cfg.GlyphRanges = glyph_ranges;
	return AddFont(&font_cfg);
}

int ImFontAtlas::AddCustomRectRegular(unsigned int id, int width, int height)
{
	ImFontAtlasCustomRect r;
	r.ID = id;
	r.Width = (unsigned short)width;
	r.Height = (unsigned short)height;
	CustomRects.push_back(r);
	return CustomRects.Size - 1; // Return index
}

int ImFontAtlas::AddCustomRectFontGlyph(ImFont* font, ImWchar id, int width, int height, float advance_x, const ImVec2& offset)
{
	ImFontAtlasCustomRect r;
	r.ID = id;
	r.Width = (unsigned short)width;
	r.Height = (unsigned short)height;
	r.GlyphAdvanceX = advance_x;
	r.GlyphOffset = offset;
	r.Font = font;
	CustomRects.push_back(r);
	return CustomRects.Size - 1; // Return index
}

void ImFontAtlas::CalcCustomRectUV(const ImFontAtlasCustomRect* rect, ImVec2* out_uv_min, ImVec2* out_uv_max) const
{
	*out_uv_min = ImVec2((float)rect->X * TexUvScale.x, (float)rect->Y * TexUvScale.y);
	*out_uv_max = ImVec2((float)(rect->X + rect->Width) * TexUvScale.x, (float)(rect->Y + rect->Height) * TexUvScale.y);
}

bool ImFontAtlas::GetMouseCursorTexData(ImGuiMouseCursor cursor_type, ImVec2* out_offset, ImVec2* out_size, ImVec2 out_uv_border[2], ImVec2 out_uv_fill[2])
{
	if (cursor_type <= ImGuiMouseCursor_None || cursor_type >= ImGuiMouseCursor_COUNT)
		return false;
	if (Flags & ImFontAtlasFlags_NoMouseCursors)
		return false;
	ImFontAtlasCustomRect& r = CustomRects[CustomRectIds[0]];
	ImVec2 pos = FONT_ATLAS_DEFAULT_TEX_CURSOR_DATA[cursor_type][0] + ImVec2((float)r.X, (float)r.Y);
	ImVec2 size = FONT_ATLAS_DEFAULT_TEX_CURSOR_DATA[cursor_type][1];
	*out_size = size;
	*out_offset = FONT_ATLAS_DEFAULT_TEX_CURSOR_DATA[cursor_type][2];
	out_uv_border[0] = (pos)* TexUvScale;
	out_uv_border[1] = (pos + size) * TexUvScale;
	pos.x += FONT_ATLAS_DEFAULT_TEX_DATA_W_HALF + 1;
	out_uv_fill[0] = (pos)* TexUvScale;
	out_uv_fill[1] = (pos + size) * TexUvScale;
	return true;
}

bool ImFontAtlas::Build()
{
	return ImFontAtlasBuildWithStbTruetype(this);
}

void ImFontAtlasBuildMultiplyCalcLookupTable(unsigned char out_table[256], float in_brighten_factor)
{
	for (unsigned int i = 0; i < 256; i++)
	{
		unsigned int value = (unsigned int)(i * in_brighten_factor);
		out_table[i] = value > 255 ? 255 : (value & 0xFF);
	}
}

void ImFontAtlasBuildMultiplyRectAlpha8(const unsigned char table[256], unsigned char* pixels, int x, int y, int w, int h, int stride)
{
	unsigned char* data = pixels + x + y * stride;
	for (int j = h; j > 0; j--, data += stride)
		for (int i = 0; i < w; i++)
			data[i] = table[data[i]];
}

struct ImFontBuildSrcData
{
	stbtt_fontinfo FontInfo;
	stbtt_pack_range PackRange; // Hold the list of codepoints to pack (essentially points to Codepoints.Data)
	stbrp_rect* Rects; // Rectangle to pack. We first fill in their size and the packer will give us their position.
	stbtt_packedchar* PackedChars; // Output glyphs
	const ImWchar* SrcRanges; // Ranges as requested by user (user is allowed to request too much, e.g. 0x0020..0xFFFF)
	int DstIndex; // Index into atlas->Fonts[] and dst_tmp_array[]
	int GlyphsHighest; // Highest requested codepoint
	int GlyphsCount; // Glyph count (excluding missing glyphs and glyphs already set by an earlier source font)
	ImBitVector GlyphsSet; // Glyph bit map (random access, 1-bit per codepoint. This will be a maximum of 8KB)
	ImVector<int> GlyphsList; // Glyph codepoints list (flattened version of GlyphsMap)
};

struct ImFontBuildDstData
{
	int SrcCount; // Number of source fonts targeting this destination font.
	int GlyphsHighest;
	int GlyphsCount;
	ImBitVector GlyphsSet; // This is used to resolve collision when multiple sources are merged into a same destination font.
};

static void UnpackBitVectorToFlatIndexList(const ImBitVector* in, ImVector<int>* out)
{
	const ImU32* it_begin = in->Storage.begin();
	const ImU32* it_end = in->Storage.end();
	for (const ImU32* it = it_begin; it < it_end; it++)
		if (ImU32 entries_32 = *it)
			for (ImU32 bit_n = 0; bit_n < 32; bit_n++)
				if (entries_32 & ((ImU32)1 << bit_n))
					out->push_back((int)(((it - it_begin) << 5) + bit_n));
}

bool ImFontAtlasBuildWithStbTruetype(ImFontAtlas* atlas)
{
	ImFontAtlasBuildInit(atlas);

	// Clear atlas
	atlas->TexID = (ImTextureID)NULL;
	atlas->TexWidth = atlas->TexHeight = 0;
	atlas->TexUvScale = ImVec2(0.0f, 0.0f);
	atlas->TexUvWhitePixel = ImVec2(0.0f, 0.0f);
	atlas->ClearTexData();

	// Temporary storage for building
	ImVector<ImFontBuildSrcData> src_tmp_array;
	ImVector<ImFontBuildDstData> dst_tmp_array;
	src_tmp_array.resize(atlas->ConfigData.Size);
	dst_tmp_array.resize(atlas->Fonts.Size);
	memset(src_tmp_array.Data, 0, (size_t)src_tmp_array.size_in_bytes());
	memset(dst_tmp_array.Data, 0, (size_t)dst_tmp_array.size_in_bytes());

	// 1. Initialize font loading structure, check font data validity
	for (int src_i = 0; src_i < atlas->ConfigData.Size; src_i++)
	{
		ImFontBuildSrcData& src_tmp = src_tmp_array[src_i];
		ImFontConfig& cfg = atlas->ConfigData[src_i];

		// Find index from cfg.DstFont (we allow the user to set cfg.DstFont. Also it makes casual debugging nicer than when storing indices)
		src_tmp.DstIndex = -1;
		for (int output_i = 0; output_i < atlas->Fonts.Size && src_tmp.DstIndex == -1; output_i++)
			if (cfg.DstFont == atlas->Fonts[output_i])
				src_tmp.DstIndex = output_i;
		if (src_tmp.DstIndex == -1)
			return false;

		// Initialize helper structure for font loading and verify that the TTF/OTF data is correct
		const int font_offset = stbtt_GetFontOffsetForIndex((unsigned char*)cfg.FontData, cfg.FontNo);
		if (!stbtt_InitFont(&src_tmp.FontInfo, (unsigned char*)cfg.FontData, font_offset))
			return false;

		// Measure highest codepoints
		ImFontBuildDstData& dst_tmp = dst_tmp_array[src_tmp.DstIndex];
		src_tmp.SrcRanges = cfg.GlyphRanges ? cfg.GlyphRanges : atlas->GetGlyphRangesChineseFull();
		for (const ImWchar* src_range = src_tmp.SrcRanges; src_range[0] && src_range[1]; src_range += 2)
			src_tmp.GlyphsHighest = ImMax(src_tmp.GlyphsHighest, (int)src_range[1]);
		dst_tmp.SrcCount++;
		dst_tmp.GlyphsHighest = ImMax(dst_tmp.GlyphsHighest, src_tmp.GlyphsHighest);
	}

	// 2. For every requested codepoint, check for their presence in the font data, and handle redundancy or overlaps between source fonts to avoid unused glyphs.
	int total_glyphs_count = 0;
	for (int src_i = 0; src_i < src_tmp_array.Size; src_i++)
	{
		ImFontBuildSrcData& src_tmp = src_tmp_array[src_i];
		ImFontBuildDstData& dst_tmp = dst_tmp_array[src_tmp.DstIndex];
		src_tmp.GlyphsSet.Create(src_tmp.GlyphsHighest + 1);
		if (dst_tmp.GlyphsSet.Storage.empty())
			dst_tmp.GlyphsSet.Create(dst_tmp.GlyphsHighest + 1);

		for (const ImWchar* src_range = src_tmp.SrcRanges; src_range[0] && src_range[1]; src_range += 2)
			for (unsigned int codepoint = src_range[0]; codepoint <= src_range[1]; codepoint++)
			{
				if (dst_tmp.GlyphsSet.TestBit(codepoint)) // Don't overwrite existing glyphs. We could make this an option for MergeMode (e.g. MergeOverwrite==true)
					continue;
				if (!stbtt_FindGlyphIndex(&src_tmp.FontInfo, codepoint)) // It is actually in the font?
					continue;

				// Add to avail set/counters
				src_tmp.GlyphsCount++;
				dst_tmp.GlyphsCount++;
				src_tmp.GlyphsSet.SetBit(codepoint);
				dst_tmp.GlyphsSet.SetBit(codepoint);
				total_glyphs_count++;
			}
	}

	// 3. Unpack our bit map into a flat list (we now have all the Unicode points that we know are requested _and_ available _and_ not overlapping another)
	for (int src_i = 0; src_i < src_tmp_array.Size; src_i++)
	{
		ImFontBuildSrcData& src_tmp = src_tmp_array[src_i];
		src_tmp.GlyphsList.reserve(src_tmp.GlyphsCount);
		UnpackBitVectorToFlatIndexList(&src_tmp.GlyphsSet, &src_tmp.GlyphsList);
		src_tmp.GlyphsSet.Clear();
	}
	for (int dst_i = 0; dst_i < dst_tmp_array.Size; dst_i++)
		dst_tmp_array[dst_i].GlyphsSet.Clear();
	dst_tmp_array.clear();

	// Allocate packing character data and flag packed characters buffer as non-packed (x0=y0=x1=y1=0)
	// (We technically don't need to zero-clear buf_rects, but let's do it for the sake of sanity)
	ImVector<stbrp_rect> buf_rects;
	ImVector<stbtt_packedchar> buf_packedchars;
	buf_rects.resize(total_glyphs_count);
	buf_packedchars.resize(total_glyphs_count);
	memset(buf_rects.Data, 0, (size_t)buf_rects.size_in_bytes());
	memset(buf_packedchars.Data, 0, (size_t)buf_packedchars.size_in_bytes());

	// 4. Gather glyphs sizes so we can pack them in our virtual canvas.
	int total_surface = 0;
	int buf_rects_out_n = 0;
	int buf_packedchars_out_n = 0;
	for (int src_i = 0; src_i < src_tmp_array.Size; src_i++)
	{
		ImFontBuildSrcData& src_tmp = src_tmp_array[src_i];
		if (src_tmp.GlyphsCount == 0)
			continue;

		src_tmp.Rects = &buf_rects[buf_rects_out_n];
		src_tmp.PackedChars = &buf_packedchars[buf_packedchars_out_n];
		buf_rects_out_n += src_tmp.GlyphsCount;
		buf_packedchars_out_n += src_tmp.GlyphsCount;

		// Convert our ranges in the format stb_truetype wants
		ImFontConfig& cfg = atlas->ConfigData[src_i];
		src_tmp.PackRange.font_size = cfg.SizePixels;
		src_tmp.PackRange.first_unicode_codepoint_in_range = 0;
		src_tmp.PackRange.array_of_unicode_codepoints = src_tmp.GlyphsList.Data;
		src_tmp.PackRange.num_chars = src_tmp.GlyphsList.Size;
		src_tmp.PackRange.chardata_for_range = src_tmp.PackedChars;
		src_tmp.PackRange.h_oversample = (unsigned char)cfg.OversampleH;
		src_tmp.PackRange.v_oversample = (unsigned char)cfg.OversampleV;

		// Gather the sizes of all rectangles we will need to pack (this loop is based on stbtt_PackFontRangesGatherRects)
		const float scale = (cfg.SizePixels > 0) ? stbtt_ScaleForPixelHeight(&src_tmp.FontInfo, cfg.SizePixels) : stbtt_ScaleForMappingEmToPixels(&src_tmp.FontInfo, -cfg.SizePixels);
		const int padding = atlas->TexGlyphPadding;
		for (int glyph_i = 0; glyph_i < src_tmp.GlyphsList.Size; glyph_i++)
		{
			int x0, y0, x1, y1;
			const int glyph_index_in_font = stbtt_FindGlyphIndex(&src_tmp.FontInfo, src_tmp.GlyphsList[glyph_i]);
			stbtt_GetGlyphBitmapBoxSubpixel(&src_tmp.FontInfo, glyph_index_in_font, scale * cfg.OversampleH, scale * cfg.OversampleV, 0, 0, &x0, &y0, &x1, &y1);
			src_tmp.Rects[glyph_i].w = (stbrp_coord)(x1 - x0 + padding + cfg.OversampleH - 1);
			src_tmp.Rects[glyph_i].h = (stbrp_coord)(y1 - y0 + padding + cfg.OversampleV - 1);
			total_surface += src_tmp.Rects[glyph_i].w * src_tmp.Rects[glyph_i].h;
		}
	}

	// We need a width for the skyline algorithm, any width!
	// The exact width doesn't really matter much, but some API/GPU have texture size limitations and increasing width can decrease height.
	// User can override TexDesiredWidth and TexGlyphPadding if they wish, otherwise we use a simple heuristic to select the width based on expected surface.
	const int surface_sqrt = (int)ImSqrt((float)total_surface) + 1;
	atlas->TexHeight = 0;
	if (atlas->TexDesiredWidth > 0)
		atlas->TexWidth = atlas->TexDesiredWidth;
	else
		atlas->TexWidth = (surface_sqrt >= 4096 * 0.7f) ? 4096 : (surface_sqrt >= 2048 * 0.7f) ? 2048 : (surface_sqrt >= 1024 * 0.7f) ? 1024 : 512;

	// 5. Start packing
	// Pack our extra data rectangles first, so it will be on the upper-left corner of our texture (UV will have small values).
	const int TEX_HEIGHT_MAX = 1024 * 32;
	stbtt_pack_context spc = {};
	stbtt_PackBegin(&spc, NULL, atlas->TexWidth, TEX_HEIGHT_MAX, 0, atlas->TexGlyphPadding, NULL);
	ImFontAtlasBuildPackCustomRects(atlas, spc.pack_info);

	// 6. Pack each source font. No rendering yet, we are working with rectangles in an infinitely tall texture at this point.
	for (int src_i = 0; src_i < src_tmp_array.Size; src_i++)
	{
		ImFontBuildSrcData& src_tmp = src_tmp_array[src_i];
		if (src_tmp.GlyphsCount == 0)
			continue;

		stbrp_pack_rects((stbrp_context*)spc.pack_info, src_tmp.Rects, src_tmp.GlyphsCount);

		// Extend texture height and mark missing glyphs as non-packed so we won't render them.
		// FIXME: We are not handling packing failure here (would happen if we got off TEX_HEIGHT_MAX or if a single if larger than TexWidth?)
		for (int glyph_i = 0; glyph_i < src_tmp.GlyphsCount; glyph_i++)
			if (src_tmp.Rects[glyph_i].was_packed)
				atlas->TexHeight = ImMax(atlas->TexHeight, src_tmp.Rects[glyph_i].y + src_tmp.Rects[glyph_i].h);
	}

	// 7. Allocate texture
	atlas->TexHeight = (atlas->Flags & ImFontAtlasFlags_NoPowerOfTwoHeight) ? (atlas->TexHeight + 1) : ImUpperPowerOfTwo(atlas->TexHeight);
	atlas->TexUvScale = ImVec2(1.0f / atlas->TexWidth, 1.0f / atlas->TexHeight);
	atlas->TexPixelsAlpha8 = (unsigned char*)ImGui::MemAlloc(atlas->TexWidth * atlas->TexHeight);
	memset(atlas->TexPixelsAlpha8, 0, atlas->TexWidth * atlas->TexHeight);
	spc.pixels = atlas->TexPixelsAlpha8;
	spc.height = atlas->TexHeight;

	// 8. Render/rasterize font characters into the texture
	for (int src_i = 0; src_i < src_tmp_array.Size; src_i++)
	{
		ImFontConfig& cfg = atlas->ConfigData[src_i];
		ImFontBuildSrcData& src_tmp = src_tmp_array[src_i];
		if (src_tmp.GlyphsCount == 0)
			continue;

		stbtt_PackFontRangesRenderIntoRects(&spc, &src_tmp.FontInfo, &src_tmp.PackRange, 1, src_tmp.Rects);

		// Apply multiply operator
		if (cfg.RasterizerMultiply != 1.0f)
		{
			unsigned char multiply_table[256];
			ImFontAtlasBuildMultiplyCalcLookupTable(multiply_table, cfg.RasterizerMultiply);
			stbrp_rect* r = &src_tmp.Rects[0];
			for (int glyph_i = 0; glyph_i < src_tmp.GlyphsCount; glyph_i++, r++)
				if (r->was_packed)
					ImFontAtlasBuildMultiplyRectAlpha8(multiply_table, atlas->TexPixelsAlpha8, r->x, r->y, r->w, r->h, atlas->TexWidth * 1);
		}
		src_tmp.Rects = NULL;
	}

	// End packing
	stbtt_PackEnd(&spc);
	buf_rects.clear();

	// 9. Setup ImFont and glyphs for runtime
	for (int src_i = 0; src_i < src_tmp_array.Size; src_i++)
	{
		ImFontBuildSrcData& src_tmp = src_tmp_array[src_i];
		if (src_tmp.GlyphsCount == 0)
			continue;

		ImFontConfig& cfg = atlas->ConfigData[src_i];
		ImFont* dst_font = cfg.DstFont; // We can have multiple input fonts writing into a same destination font (when using MergeMode=true)

		const float font_scale = stbtt_ScaleForPixelHeight(&src_tmp.FontInfo, cfg.SizePixels);
		int unscaled_ascent, unscaled_descent, unscaled_line_gap;
		stbtt_GetFontVMetrics(&src_tmp.FontInfo, &unscaled_ascent, &unscaled_descent, &unscaled_line_gap);

		const float ascent = ImFloor(unscaled_ascent * font_scale + ((unscaled_ascent > 0.0f) ? +1 : -1));
		const float descent = ImFloor(unscaled_descent * font_scale + ((unscaled_descent > 0.0f) ? +1 : -1));
		ImFontAtlasBuildSetupFont(atlas, dst_font, &cfg, ascent, descent);
		const float font_off_x = cfg.GlyphOffset.x;
		const float font_off_y = cfg.GlyphOffset.y + IM_ROUND(dst_font->Ascent);

		for (int glyph_i = 0; glyph_i < src_tmp.GlyphsCount; glyph_i++)
		{
			const int codepoint = src_tmp.GlyphsList[glyph_i];
			const stbtt_packedchar& pc = src_tmp.PackedChars[glyph_i];

			const float char_advance_x_org = pc.xadvance;
			const float char_advance_x_mod = ImClamp(char_advance_x_org, cfg.GlyphMinAdvanceX, cfg.GlyphMaxAdvanceX);
			float char_off_x = font_off_x;
			if (char_advance_x_org != char_advance_x_mod)
				char_off_x += cfg.PixelSnapH ? ImFloor((char_advance_x_mod - char_advance_x_org) * 0.5f) : (char_advance_x_mod - char_advance_x_org) * 0.5f;

			// Register glyph
			stbtt_aligned_quad q;
			float dummy_x = 0.0f, dummy_y = 0.0f;
			stbtt_GetPackedQuad(src_tmp.PackedChars, atlas->TexWidth, atlas->TexHeight, glyph_i, &dummy_x, &dummy_y, &q, 0);
			dst_font->AddGlyph((ImWchar)codepoint, q.x0 + char_off_x, q.y0 + font_off_y, q.x1 + char_off_x, q.y1 + font_off_y, q.s0, q.t0, q.s1, q.t1, char_advance_x_mod);
		}
	}

	// Cleanup temporary (ImVector doesn't honor destructor)
	for (int src_i = 0; src_i < src_tmp_array.Size; src_i++)
		src_tmp_array[src_i].~ImFontBuildSrcData();

	ImFontAtlasBuildFinish(atlas);
	return true;
}

void ImFontAtlasBuildInit(ImFontAtlas* atlas)
{
	if (atlas->CustomRectIds[0] >= 0)
		return;
	if (!(atlas->Flags & ImFontAtlasFlags_NoMouseCursors))
		atlas->CustomRectIds[0] = atlas->AddCustomRectRegular(FONT_ATLAS_DEFAULT_TEX_DATA_ID, FONT_ATLAS_DEFAULT_TEX_DATA_W_HALF * 2 + 1, FONT_ATLAS_DEFAULT_TEX_DATA_H);
	else
		atlas->CustomRectIds[0] = atlas->AddCustomRectRegular(FONT_ATLAS_DEFAULT_TEX_DATA_ID, 2, 2);
}

void ImFontAtlasBuildSetupFont(ImFontAtlas* atlas, ImFont* font, ImFontConfig* font_config, float ascent, float descent)
{
	if (!font_config->MergeMode)
	{
		font->ClearOutputData();
		font->FontSize = font_config->SizePixels;
		font->ConfigData = font_config;
		font->ContainerAtlas = atlas;
		font->Ascent = ascent;
		font->Descent = descent;
	}
	font->ConfigDataCount++;
}

void ImFontAtlasBuildPackCustomRects(ImFontAtlas* atlas, void* stbrp_context_opaque)
{
	stbrp_context* pack_context = (stbrp_context*)stbrp_context_opaque;

	ImVector<ImFontAtlasCustomRect>& user_rects = atlas->CustomRects;

	ImVector<stbrp_rect> pack_rects;
	pack_rects.resize(user_rects.Size);
	memset(pack_rects.Data, 0, (size_t)pack_rects.size_in_bytes());
	for (int i = 0; i < user_rects.Size; i++)
	{
		pack_rects[i].w = user_rects[i].Width;
		pack_rects[i].h = user_rects[i].Height;
	}
	stbrp_pack_rects(pack_context, &pack_rects[0], pack_rects.Size);
	for (int i = 0; i < pack_rects.Size; i++)
		if (pack_rects[i].was_packed)
		{
			user_rects[i].X = pack_rects[i].x;
			user_rects[i].Y = pack_rects[i].y;
			atlas->TexHeight = ImMax(atlas->TexHeight, pack_rects[i].y + pack_rects[i].h);
		}
}

static void ImFontAtlasBuildRenderDefaultTexData(ImFontAtlas* atlas)
{
	ImFontAtlasCustomRect& r = atlas->CustomRects[atlas->CustomRectIds[0]];

	const int w = atlas->TexWidth;
	if (!(atlas->Flags & ImFontAtlasFlags_NoMouseCursors))
	{
		// Render/copy pixels
		for (int y = 0, n = 0; y < FONT_ATLAS_DEFAULT_TEX_DATA_H; y++)
			for (int x = 0; x < FONT_ATLAS_DEFAULT_TEX_DATA_W_HALF; x++, n++)
			{
				const int offset0 = (int)(r.X + x) + (int)(r.Y + y) * w;
				const int offset1 = offset0 + FONT_ATLAS_DEFAULT_TEX_DATA_W_HALF + 1;
				atlas->TexPixelsAlpha8[offset0] = FONT_ATLAS_DEFAULT_TEX_DATA_PIXELS[n] == '.' ? 0xFF : 0x00;
				atlas->TexPixelsAlpha8[offset1] = FONT_ATLAS_DEFAULT_TEX_DATA_PIXELS[n] == 'X' ? 0xFF : 0x00;
			}
	}
	else
	{
		const int offset = (int)(r.X) + (int)(r.Y) * w;
		atlas->TexPixelsAlpha8[offset] = atlas->TexPixelsAlpha8[offset + 1] = atlas->TexPixelsAlpha8[offset + w] = atlas->TexPixelsAlpha8[offset + w + 1] = 0xFF;
	}
	atlas->TexUvWhitePixel = ImVec2((r.X + 0.5f) * atlas->TexUvScale.x, (r.Y + 0.5f) * atlas->TexUvScale.y);
}

void ImFontAtlasBuildFinish(ImFontAtlas* atlas)
{
	// Render into our custom data block
	ImFontAtlasBuildRenderDefaultTexData(atlas);

	// Register custom rectangle glyphs
	for (int i = 0; i < atlas->CustomRects.Size; i++)
	{
		const ImFontAtlasCustomRect& r = atlas->CustomRects[i];
		if (r.Font == NULL || r.ID >= 0x110000)
			continue;

		ImVec2 uv0, uv1;
		atlas->CalcCustomRectUV(&r, &uv0, &uv1);
		r.Font->AddGlyph((ImWchar)r.ID, r.GlyphOffset.x, r.GlyphOffset.y, r.GlyphOffset.x + r.Width, r.GlyphOffset.y + r.Height, uv0.x, uv0.y, uv1.x, uv1.y, r.GlyphAdvanceX);
	}

	// Build all fonts lookup tables
	for (int i = 0; i < atlas->Fonts.Size; i++)
		if (atlas->Fonts[i]->DirtyLookupTables)
			atlas->Fonts[i]->BuildLookupTable();

	// Ellipsis character is required for rendering elided text. We prefer using U+2026 (horizontal ellipsis).
	// However some old fonts may contain ellipsis at U+0085. Here we auto-detect most suitable ellipsis character.
	// FIXME: Also note that 0x2026 is currently seldomly included in our font ranges. Because of this we are more likely to use three individual dots.
	for (int i = 0; i < atlas->Fonts.size(); i++)
	{
		ImFont* font = atlas->Fonts[i];
		if (font->EllipsisChar != (ImWchar)-1)
			continue;
		const ImWchar ellipsis_variants[] = { (ImWchar)0x2026, (ImWchar)0x0085 };
		for (int j = 0; j < ARRAYSIZE(ellipsis_variants); j++)
			if (font->FindGlyphNoFallback(ellipsis_variants[j]) != NULL) // Verify glyph exists
			{
				font->EllipsisChar = ellipsis_variants[j];
				break;
			}
	}
}

const ImWchar* ImFontAtlas::GetGlyphRangesChineseFull()
{
	static const ImWchar ranges[] =
	{
	 0x0020, 0x00FF, // Basic Latin + Latin Supplement
	 0x2000, 0x206F, // General Punctuation
	 0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
	 0x31F0, 0x31FF, // Katakana Phonetic Extensions
	 0xFF00, 0xFFEF, // Half-width characters
	 0x4e00, 0x9FAF, // CJK Ideograms
	 0,
	};
	return &ranges[0];
}

static void UnpackAccumulativeOffsetsIntoRanges(int base_codepoint, const short* accumulative_offsets, int accumulative_offsets_count, ImWchar* out_ranges)
{
	for (int n = 0; n < accumulative_offsets_count; n++, out_ranges += 2)
	{
		out_ranges[0] = out_ranges[1] = (ImWchar)(base_codepoint + accumulative_offsets[n]);
		base_codepoint += accumulative_offsets[n];
	}
	out_ranges[0] = 0;
}

void ImFontGlyphRangesBuilder::AddText(const char* text, const char* text_end)
{
	while (text_end ? (text < text_end) : *text)
	{
		unsigned int c = 0;
		int c_len = ImTextCharFromUtf8(&c, text, text_end);
		text += c_len;
		if (c_len == 0)
			break;
		AddChar((ImWchar)c);
	}
}

void ImFontGlyphRangesBuilder::AddRanges(const ImWchar* ranges)
{
	for (; ranges[0]; ranges += 2)
		for (ImWchar c = ranges[0]; c <= ranges[1]; c++)
			AddChar(c);
}

void ImFontGlyphRangesBuilder::BuildRanges(ImVector<ImWchar>* out_ranges)
{
	const int max_codepoint = 0xFFFF;
	for (int n = 0; n <= max_codepoint; n++)
		if (GetBit(n))
		{
			out_ranges->push_back((ImWchar)n);
			while (n < max_codepoint && GetBit(n + 1))
				n++;
			out_ranges->push_back((ImWchar)n);
		}
	out_ranges->push_back(0);
}

ImFont::ImFont()
{
	FontSize = 0.0f;
	FallbackAdvanceX = 0.0f;
	FallbackChar = (ImWchar)'?';
	EllipsisChar = (ImWchar)-1;
	DisplayOffset = ImVec2(0.0f, 0.0f);
	FallbackGlyph = NULL;
	ContainerAtlas = NULL;
	ConfigData = NULL;
	ConfigDataCount = 0;
	DirtyLookupTables = false;
	Scale = 1.0f;
	Ascent = Descent = 0.0f;
	MetricsTotalSurface = 0;
	memset(Used4kPagesMap, 0, sizeof(Used4kPagesMap));
}

ImFont::~ImFont()
{
	ClearOutputData();
}

void ImFont::ClearOutputData()
{
	FontSize = 0.0f;
	FallbackAdvanceX = 0.0f;
	Glyphs.clear();
	IndexAdvanceX.clear();
	IndexLookup.clear();
	FallbackGlyph = NULL;
	ContainerAtlas = NULL;
	DirtyLookupTables = true;
	Ascent = Descent = 0.0f;
	MetricsTotalSurface = 0;
}

void ImFont::BuildLookupTable()
{
	int max_codepoint = 0;
	for (int i = 0; i != Glyphs.Size; i++)
		max_codepoint = ImMax(max_codepoint, (int)Glyphs[i].Codepoint);

	// Build lookup table
	IndexAdvanceX.clear();
	IndexLookup.clear();
	DirtyLookupTables = false;
	memset(Used4kPagesMap, 0, sizeof(Used4kPagesMap));
	GrowIndex(max_codepoint + 1);
	for (int i = 0; i < Glyphs.Size; i++)
	{
		int codepoint = (int)Glyphs[i].Codepoint;
		IndexAdvanceX[codepoint] = Glyphs[i].AdvanceX;
		IndexLookup[codepoint] = (ImWchar)i;

		// Mark 4K page as used
		const int page_n = codepoint / 4096;
		Used4kPagesMap[page_n >> 3] |= 1 << (page_n & 7);
	}

	// Create a glyph to handle TAB
	// FIXME: Needs proper TAB handling but it needs to be contextualized (or we could arbitrary say that each string starts at "column 0" ?)
	if (FindGlyph((ImWchar)' '))
	{
		if (Glyphs.back().Codepoint != '\t') // So we can call this function multiple times (FIXME: Flaky)
			Glyphs.resize(Glyphs.Size + 1);
		ImFontGlyph& tab_glyph = Glyphs.back();
		tab_glyph = *FindGlyph((ImWchar)' ');
		tab_glyph.Codepoint = '\t';
		tab_glyph.AdvanceX *= 4;
		IndexAdvanceX[(int)tab_glyph.Codepoint] = (float)tab_glyph.AdvanceX;
		IndexLookup[(int)tab_glyph.Codepoint] = (ImWchar)(Glyphs.Size - 1);
	}

	// Mark special glyphs as not visible (note that AddGlyph already mark as non-visible glyphs with zero-size polygons)
	SetGlyphVisible((ImWchar)' ', false);
	SetGlyphVisible((ImWchar)'\t', false);

	// Setup fall-backs
	FallbackGlyph = FindGlyphNoFallback(FallbackChar);
	FallbackAdvanceX = FallbackGlyph ? FallbackGlyph->AdvanceX : 0.0f;
	for (int i = 0; i < max_codepoint + 1; i++)
		if (IndexAdvanceX[i] < 0.0f)
			IndexAdvanceX[i] = FallbackAdvanceX;
}

bool ImFont::IsGlyphRangeUnused(unsigned int c_begin, unsigned int c_last)
{
	unsigned int page_begin = (c_begin / 4096);
	unsigned int page_last = (c_last / 4096);
	for (unsigned int page_n = page_begin; page_n <= page_last; page_n++)
		if ((page_n >> 3) < sizeof(Used4kPagesMap))
			if (Used4kPagesMap[page_n >> 3] & (1 << (page_n & 7)))
				return false;
	return true;
}

void ImFont::SetGlyphVisible(ImWchar c, bool visible)
{
	if (ImFontGlyph* glyph = (ImFontGlyph*)(void*)FindGlyph((ImWchar)c))
		glyph->Visible = visible ? 1 : 0;
}

void ImFont::SetFallbackChar(ImWchar c)
{
	FallbackChar = c;
	BuildLookupTable();
}

void ImFont::GrowIndex(int new_size)
{
	if (new_size <= IndexLookup.Size)
		return;
	IndexAdvanceX.resize(new_size, -1.0f);
	IndexLookup.resize(new_size, (ImWchar)-1);
}

void ImFont::AddGlyph(ImWchar codepoint, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float advance_x)
{
	Glyphs.resize(Glyphs.Size + 1);
	ImFontGlyph& glyph = Glyphs.back();
	glyph.Codepoint = (unsigned int)codepoint;
	glyph.Visible = (x0 != x1) && (y0 != y1);
	glyph.X0 = x0;
	glyph.Y0 = y0;
	glyph.X1 = x1;
	glyph.Y1 = y1;
	glyph.U0 = u0;
	glyph.V0 = v0;
	glyph.U1 = u1;
	glyph.V1 = v1;
	glyph.AdvanceX = advance_x + ConfigData->GlyphExtraSpacing.x; // Bake spacing into AdvanceX

	if (ConfigData->PixelSnapH)
		glyph.AdvanceX = IM_ROUND(glyph.AdvanceX);

	// Compute rough surface usage metrics (+1 to account for average padding, +0.99 to round)
	DirtyLookupTables = true;
	MetricsTotalSurface += (int)((glyph.U1 - glyph.U0) * ContainerAtlas->TexWidth + 1.99f) * (int)((glyph.V1 - glyph.V0) * ContainerAtlas->TexHeight + 1.99f);
}

void ImFont::AddRemapChar(ImWchar dst, ImWchar src, bool overwrite_dst)
{
	unsigned int index_size = (unsigned int)IndexLookup.Size;

	if (dst < index_size && IndexLookup.Data[dst] == (ImWchar)-1 && !overwrite_dst) // 'dst' already exists
		return;
	if (src >= index_size && dst >= index_size) // both 'dst' and 'src' don't exist -> no-op
		return;

	GrowIndex(dst + 1);
	IndexLookup[dst] = (src < index_size) ? IndexLookup.Data[src] : (ImWchar)-1;
	IndexAdvanceX[dst] = (src < index_size) ? IndexAdvanceX.Data[src] : 1.0f;
}

const ImFontGlyph* ImFont::FindGlyph(ImWchar c) const
{
	if (c >= (size_t)IndexLookup.Size)
		return FallbackGlyph;
	const ImWchar i = IndexLookup.Data[c];
	if (i == (ImWchar)-1)
		return FallbackGlyph;
	return &Glyphs.Data[i];
}

const ImFontGlyph* ImFont::FindGlyphNoFallback(ImWchar c) const
{
	if (c >= (size_t)IndexLookup.Size)
		return NULL;
	const ImWchar i = IndexLookup.Data[c];
	if (i == (ImWchar)-1)
		return NULL;
	return &Glyphs.Data[i];
}

const char* ImFont::CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const
{
	// Simple word-wrapping for English, not full-featured. Please submit failing cases!
	// FIXME: Much possible improvements (don't cut things like "word !", "word!!!" but cut within "word,,,,", more sensible support for punctuations, support for Unicode punctuations, etc.)

	// For references, possible wrap point marked with ^
	// "aaa bbb, ccc,ddd. eee fff. ggg!"
	// ^ ^ ^ ^ ^__ ^ ^

	// List of hardcoded separators: .,;!?'"

	// Skip extra blanks after a line returns (that includes not counting them in width computation)
	// e.g. "Hello world" --> "Hello" "World"

	// Cut words that cannot possibly fit within one line.
	// e.g.: "The tropical fish" with ~5 characters worth of width --> "The tr" "opical" "fish"

	float line_width = 0.0f;
	float word_width = 0.0f;
	float blank_width = 0.0f;
	wrap_width /= scale; // We work with unscaled widths to avoid scaling every characters

	const char* word_end = text;
	const char* prev_word_end = NULL;
	bool inside_word = true;

	const char* s = text;
	while (s < text_end)
	{
		unsigned int c = (unsigned int)*s;
		const char* next_s;
		if (c < 0x80)
			next_s = s + 1;
		else
			next_s = s + ImTextCharFromUtf8(&c, s, text_end);
		if (c == 0)
			break;

		if (c < 32)
		{
			if (c == '\n')
			{
				line_width = word_width = blank_width = 0.0f;
				inside_word = true;
				s = next_s;
				continue;
			}
			if (c == '\r')
			{
				s = next_s;
				continue;
			}
		}

		const float char_width = ((int)c < IndexAdvanceX.Size ? IndexAdvanceX.Data[c] : FallbackAdvanceX);
		if (ImCharIsBlankW(c))
		{
			if (inside_word)
			{
				line_width += blank_width;
				blank_width = 0.0f;
				word_end = s;
			}
			blank_width += char_width;
			inside_word = false;
		}
		else
		{
			word_width += char_width;
			if (inside_word)
			{
				word_end = next_s;
			}
			else
			{
				prev_word_end = word_end;
				line_width += word_width + blank_width;
				word_width = blank_width = 0.0f;
			}

			// Allow wrapping after punctuation.
			inside_word = !(c == '.' || c == ',' || c == ';' || c == '!' || c == '?' || c == '\"');
		}

		// We ignore blank width at the end of the line (they can be skipped)
		if (line_width + word_width > wrap_width)
		{
			// Words that cannot possibly fit within an entire line will be cut anywhere.
			if (word_width < wrap_width)
				s = prev_word_end ? prev_word_end : word_end;
			break;
		}

		s = next_s;
	}

	return s;
}

ImVec2 ImFont::CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end, const char** remaining) const
{
	if (!text_end)
		text_end = text_begin + strlen(text_begin); // FIXME-OPT: Need to avoid this.

	const float line_height = size;
	const float scale = size / FontSize;

	ImVec2 text_size = ImVec2(0, 0);
	float line_width = 0.0f;

	const bool word_wrap_enabled = (wrap_width > 0.0f);
	const char* word_wrap_eol = NULL;

	const char* s = text_begin;
	while (s < text_end)
	{
		if (word_wrap_enabled)
		{
			// Calculate how far we can render. Requires two passes on the string data but keeps the code simple and not intrusive for what's essentially an uncommon feature.
			if (!word_wrap_eol)
			{
				word_wrap_eol = CalcWordWrapPositionA(scale, s, text_end, wrap_width - line_width);
				if (word_wrap_eol == s) // Wrap_width is too small to fit anything. Force displaying 1 character to minimize the height discontinuity.
					word_wrap_eol++; // +1 may not be a character start point in UTF-8 but it's ok because we use s >= word_wrap_eol below
			}

			if (s >= word_wrap_eol)
			{
				if (text_size.x < line_width)
					text_size.x = line_width;
				text_size.y += line_height;
				line_width = 0.0f;
				word_wrap_eol = NULL;

				// Wrapping skips upcoming blanks
				while (s < text_end)
				{
					const char c = *s;
					if (ImCharIsBlankA(c)) { s++; }
					else if (c == '\n') { s++; break; }
					else { break; }
				}
				continue;
			}
		}

		// Decode and advance source
		const char* prev_s = s;
		unsigned int c = (unsigned int)*s;
		if (c < 0x80)
		{
			s += 1;
		}
		else
		{
			s += ImTextCharFromUtf8(&c, s, text_end);
			if (c == 0) // Malformed UTF-8?
				break;
		}

		if (c < 32)
		{
			if (c == '\n')
			{
				text_size.x = ImMax(text_size.x, line_width);
				text_size.y += line_height;
				line_width = 0.0f;
				continue;
			}
			if (c == '\r')
				continue;
		}

		const float char_width = ((int)c < IndexAdvanceX.Size ? IndexAdvanceX.Data[c] : FallbackAdvanceX) * scale;
		if (line_width + char_width >= max_width)
		{
			s = prev_s;
			break;
		}

		line_width += char_width;
	}

	if (text_size.x < line_width)
		text_size.x = line_width;

	if (line_width > 0 || text_size.y == 0.0f)
		text_size.y += line_height;

	if (remaining)
		*remaining = s;

	return text_size;
}

void ImFont::RenderChar(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, ImWchar c) const
{
	const ImFontGlyph* glyph = FindGlyph(c);
	if (!glyph || !glyph->Visible)
		return;
	float scale = (size >= 0.0f) ? (size / FontSize) : 1.0f;
	pos.x = (FLOAT)(pos.x + DisplayOffset.x);
	pos.y = (FLOAT)(pos.y + DisplayOffset.y);
	draw_list->PrimReserve(6, 4);
	draw_list->PrimRectUV(ImVec2(pos.x + glyph->X0 * scale, pos.y + glyph->Y0 * scale), ImVec2(pos.x + glyph->X1 * scale, pos.y + glyph->Y1 * scale), ImVec2(glyph->U0, glyph->V0), ImVec2(glyph->U1, glyph->V1), col);
}

void ImFont::RenderText(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width, bool cpu_fine_clip) const
{
	if (!text_end)
		text_end = text_begin + strlen(text_begin); // ImGui:: functions generally already provides a valid text_end, so this is merely to handle direct calls.

	 // Align to be pixel perfect
	pos.x = (FLOAT)(pos.x + DisplayOffset.x);
	pos.y = (FLOAT)(pos.y + DisplayOffset.y);
	float x = pos.x;
	float y = pos.y;
	if (y > clip_rect.w)
		return;

	const float scale = size / FontSize;
	const float line_height = FontSize * scale;
	const bool word_wrap_enabled = (wrap_width > 0.0f);
	const char* word_wrap_eol = NULL;

	// Fast-forward to first visible line
	const char* s = text_begin;
	if (y + line_height < clip_rect.y && !word_wrap_enabled)
		while (y + line_height < clip_rect.y && s < text_end)
		{
			s = (const char*)memchr(s, '\n', text_end - s);
			s = s ? s + 1 : text_end;
			y += line_height;
		}

	// For large text, scan for the last visible line in order to avoid over-reserving in the call to PrimReserve()
	// Note that very large horizontal line will still be affected by the issue (e.g. a one megabyte string buffer without a newline will likely crash atm)
	if (text_end - s > 10000 && !word_wrap_enabled)
	{
		const char* s_end = s;
		float y_end = y;
		while (y_end < clip_rect.w && s_end < text_end)
		{
			s_end = (const char*)memchr(s_end, '\n', text_end - s_end);
			s_end = s_end ? s_end + 1 : text_end;
			y_end += line_height;
		}
		text_end = s_end;
	}
	if (s == text_end)
		return;

	// Reserve vertices for remaining worse case (over-reserving is useful and easily amortized)
	const int vtx_count_max = (int)(text_end - s) * 4;
	const int idx_count_max = (int)(text_end - s) * 6;
	const int idx_expected_size = draw_list->IdxBuffer.Size + idx_count_max;
	draw_list->PrimReserve(idx_count_max, vtx_count_max);

	ImDrawVert* vtx_write = draw_list->_VtxWritePtr;
	ImDrawIdx* idx_write = draw_list->_IdxWritePtr;
	unsigned int vtx_current_idx = draw_list->_VtxCurrentIdx;

	while (s < text_end)
	{
		if (word_wrap_enabled)
		{
			// Calculate how far we can render. Requires two passes on the string data but keeps the code simple and not intrusive for what's essentially an uncommon feature.
			if (!word_wrap_eol)
			{
				word_wrap_eol = CalcWordWrapPositionA(scale, s, text_end, wrap_width - (x - pos.x));
				if (word_wrap_eol == s) // Wrap_width is too small to fit anything. Force displaying 1 character to minimize the height discontinuity.
					word_wrap_eol++; // +1 may not be a character start point in UTF-8 but it's ok because we use s >= word_wrap_eol below
			}

			if (s >= word_wrap_eol)
			{
				x = pos.x;
				y += line_height;
				word_wrap_eol = NULL;

				// Wrapping skips upcoming blanks
				while (s < text_end)
				{
					const char c = *s;
					if (ImCharIsBlankA(c)) { s++; }
					else if (c == '\n') { s++; break; }
					else { break; }
				}
				continue;
			}
		}

		// Decode and advance source
		unsigned int c = (unsigned int)*s;
		if (c < 0x80)
		{
			s += 1;
		}
		else
		{
			s += ImTextCharFromUtf8(&c, s, text_end);
			if (c == 0) // Malformed UTF-8?
				break;
		}

		if (c < 32)
		{
			if (c == '\n')
			{
				x = pos.x;
				y += line_height;
				if (y > clip_rect.w)
					break; // break out of main loop
				continue;
			}
			if (c == '\r')
				continue;
		}

		const ImFontGlyph* glyph = FindGlyph((ImWchar)c);
		if (glyph == NULL)
			continue;

		float char_width = glyph->AdvanceX * scale;
		if (glyph->Visible)
		{
			// We don't do a second finer clipping test on the Y axis as we've already skipped anything before clip_rect.y and exit once we pass clip_rect.w
			float x1 = x + glyph->X0 * scale;
			float x2 = x + glyph->X1 * scale;
			float y1 = y + glyph->Y0 * scale;
			float y2 = y + glyph->Y1 * scale;
			if (x1 <= clip_rect.z && x2 >= clip_rect.x)
			{
				// Render a character
				float u1 = glyph->U0;
				float v1 = glyph->V0;
				float u2 = glyph->U1;
				float v2 = glyph->V1;

				// CPU side clipping used to fit text in their frame when the frame is too small. Only does clipping for axis aligned quads.
				if (cpu_fine_clip)
				{
					if (x1 < clip_rect.x)
					{
						u1 = u1 + (1.0f - (x2 - clip_rect.x) / (x2 - x1)) * (u2 - u1);
						x1 = clip_rect.x;
					}
					if (y1 < clip_rect.y)
					{
						v1 = v1 + (1.0f - (y2 - clip_rect.y) / (y2 - y1)) * (v2 - v1);
						y1 = clip_rect.y;
					}
					if (x2 > clip_rect.z)
					{
						u2 = u1 + ((clip_rect.z - x1) / (x2 - x1)) * (u2 - u1);
						x2 = clip_rect.z;
					}
					if (y2 > clip_rect.w)
					{
						v2 = v1 + ((clip_rect.w - y1) / (y2 - y1)) * (v2 - v1);
						y2 = clip_rect.w;
					}
					if (y1 >= y2)
					{
						x += char_width;
						continue;
					}
				}

				// We are NOT calling PrimRectUV() here because non-inlined causes too much overhead in a debug builds. Inlined here:
				{
					idx_write[0] = (ImDrawIdx)(vtx_current_idx); idx_write[1] = (ImDrawIdx)(vtx_current_idx + 1); idx_write[2] = (ImDrawIdx)(vtx_current_idx + 2);
					idx_write[3] = (ImDrawIdx)(vtx_current_idx); idx_write[4] = (ImDrawIdx)(vtx_current_idx + 2); idx_write[5] = (ImDrawIdx)(vtx_current_idx + 3);
					vtx_write[0].pos.x = x1; vtx_write[0].pos.y = y1; vtx_write[0].col = col; vtx_write[0].uv.x = u1; vtx_write[0].uv.y = v1;
					vtx_write[1].pos.x = x2; vtx_write[1].pos.y = y1; vtx_write[1].col = col; vtx_write[1].uv.x = u2; vtx_write[1].uv.y = v1;
					vtx_write[2].pos.x = x2; vtx_write[2].pos.y = y2; vtx_write[2].col = col; vtx_write[2].uv.x = u2; vtx_write[2].uv.y = v2;
					vtx_write[3].pos.x = x1; vtx_write[3].pos.y = y2; vtx_write[3].col = col; vtx_write[3].uv.x = u1; vtx_write[3].uv.y = v2;
					vtx_write += 4;
					vtx_current_idx += 4;
					idx_write += 6;
				}
			}
		}
		x += char_width;
	}

	// Give back unused vertices (clipped ones, blanks) ~ this is essentially a PrimUnreserve() action.
	draw_list->VtxBuffer.Size = (int)(vtx_write - draw_list->VtxBuffer.Data); // Same as calling shrink()
	draw_list->IdxBuffer.Size = (int)(idx_write - draw_list->IdxBuffer.Data);
	draw_list->CmdBuffer[draw_list->CmdBuffer.Size - 1].ElemCount -= (idx_expected_size - draw_list->IdxBuffer.Size);
	draw_list->_VtxWritePtr = vtx_write;
	draw_list->_IdxWritePtr = idx_write;
	draw_list->_VtxCurrentIdx = vtx_current_idx;
}

void ImGui::RenderArrow(ImDrawList* draw_list, ImVec2 pos, ImU32 col, ImGuiDir dir, float scale)
{
	const float h = draw_list->_Data->FontSize * 1.00f;
	float r = h * 0.40f * scale;
	ImVec2 center = pos + ImVec2(h * 0.50f, h * 0.50f * scale);

	ImVec2 a, b, c;
	switch (dir)
	{
	case ImGuiDir_Up:
	case ImGuiDir_Down:
		if (dir == ImGuiDir_Up) r = -r;
		a = ImVec2(+0.000f, +0.750f) * r;
		b = ImVec2(-0.866f, -0.750f) * r;
		c = ImVec2(+0.866f, -0.750f) * r;
		break;
	case ImGuiDir_Left:
	case ImGuiDir_Right:
		if (dir == ImGuiDir_Left) r = -r;
		a = ImVec2(+0.750f, +0.000f) * r;
		b = ImVec2(-0.750f, +0.866f) * r;
		c = ImVec2(-0.750f, -0.866f) * r;
		break;
	case ImGuiDir_None:
	case ImGuiDir_COUNT:
		break;
	}
	draw_list->AddTriangleFilled(center + a, center + b, center + c, col);
}

void ImGui::RenderBullet(ImDrawList* draw_list, ImVec2 pos, ImU32 col)
{
	draw_list->AddCircleFilled(pos, draw_list->_Data->FontSize * 0.20f, col, 8);
}

void ImGui::RenderCheckMark(ImDrawList* draw_list, ImVec2 pos, ImU32 col, float sz)
{
	float thickness = ImMax(sz / 5.0f, 1.0f);
	sz -= thickness * 0.5f;
	pos += ImVec2(thickness * 0.25f, thickness * 0.25f);

	float third = sz / 3.0f;
	float bx = pos.x + third;
	float by = pos.y + sz - third * 0.5f;
	draw_list->PathLineTo(ImVec2(bx - third, by - third));
	draw_list->PathLineTo(ImVec2(bx, by));
	draw_list->PathLineTo(ImVec2(bx + third * 2.0f, by - third * 2.0f));
	draw_list->PathStroke(col, false, thickness);
}

void ImGui::RenderMouseCursor(ImDrawList* draw_list, ImVec2 pos, float scale, ImGuiMouseCursor mouse_cursor, ImU32 col_fill, ImU32 col_border, ImU32 col_shadow)
{
	if (mouse_cursor == ImGuiMouseCursor_None)
		return;

	ImFontAtlas* font_atlas = draw_list->_Data->Font->ContainerAtlas;
	ImVec2 offset, size, uv[4];
	if (font_atlas->GetMouseCursorTexData(mouse_cursor, &offset, &size, &uv[0], &uv[2]))
	{
		pos -= offset;
		const ImTextureID tex_id = font_atlas->TexID;
		draw_list->PushTextureID(tex_id);
		draw_list->AddImage(tex_id, pos + ImVec2(1, 0)*scale, pos + ImVec2(1, 0)*scale + size * scale, uv[2], uv[3], col_shadow);
		draw_list->AddImage(tex_id, pos + ImVec2(2, 0)*scale, pos + ImVec2(2, 0)*scale + size * scale, uv[2], uv[3], col_shadow);
		draw_list->AddImage(tex_id, pos, pos + size * scale, uv[2], uv[3], col_border);
		draw_list->AddImage(tex_id, pos, pos + size * scale, uv[0], uv[1], col_fill);
		draw_list->PopTextureID();
	}
}

void ImGui::RenderArrowPointingAt(ImDrawList* draw_list, ImVec2 pos, ImVec2 half_sz, ImGuiDir direction, ImU32 col)
{
	switch (direction)
	{
	case ImGuiDir_Left: draw_list->AddTriangleFilled(ImVec2(pos.x + half_sz.x, pos.y - half_sz.y), ImVec2(pos.x + half_sz.x, pos.y + half_sz.y), pos, col); return;
	case ImGuiDir_Right: draw_list->AddTriangleFilled(ImVec2(pos.x - half_sz.x, pos.y + half_sz.y), ImVec2(pos.x - half_sz.x, pos.y - half_sz.y), pos, col); return;
	case ImGuiDir_Up: draw_list->AddTriangleFilled(ImVec2(pos.x + half_sz.x, pos.y + half_sz.y), ImVec2(pos.x - half_sz.x, pos.y + half_sz.y), pos, col); return;
	case ImGuiDir_Down: draw_list->AddTriangleFilled(ImVec2(pos.x - half_sz.x, pos.y - half_sz.y), ImVec2(pos.x + half_sz.x, pos.y - half_sz.y), pos, col); return;
	case ImGuiDir_None: case ImGuiDir_COUNT: break; // Fix warnings
	}
}

static inline float ImAcos01(float x)
{
	if (x <= 0.0f) return 3.1415926f * 0.5f;
	if (x >= 1.0f) return 0.0f;
	return ImAcos(x);
	//return (-0.69813170079773212f * x * x - 0.87266462599716477f) * x + 1.5707963267948966f; // Cheap approximation, may be enough for what we do.
}

void ImGui::RenderRectFilledRangeH(ImDrawList* draw_list, const ImRect& rect, ImU32 col, float x_start_norm, float x_end_norm, float rounding)
{
	if (x_end_norm == x_start_norm)
		return;
	if (x_start_norm > x_end_norm)
		ImSwap(x_start_norm, x_end_norm);

	ImVec2 p0 = ImVec2(ImLerp(rect.Min.x, rect.Max.x, x_start_norm), rect.Min.y);
	ImVec2 p1 = ImVec2(ImLerp(rect.Min.x, rect.Max.x, x_end_norm), rect.Max.y);
	if (rounding == 0.0f)
	{
		draw_list->AddRectFilled(p0, p1, col, 0.0f);
		return;
	}

	rounding = ImClamp(ImMin((rect.Max.x - rect.Min.x) * 0.5f, (rect.Max.y - rect.Min.y) * 0.5f) - 1.0f, 0.0f, rounding);
	const float inv_rounding = 1.0f / rounding;
	const float arc0_b = ImAcos01(1.0f - (p0.x - rect.Min.x) * inv_rounding);
	const float arc0_e = ImAcos01(1.0f - (p1.x - rect.Min.x) * inv_rounding);
	const float half_pi = 3.1415926f * 0.5f; // We will == compare to this because we know this is the exact value ImAcos01 can return.
	const float x0 = ImMax(p0.x, rect.Min.x + rounding);
	if (arc0_b == arc0_e)
	{
		draw_list->PathLineTo(ImVec2(x0, p1.y));
		draw_list->PathLineTo(ImVec2(x0, p0.y));
	}
	else if (arc0_b == 0.0f && arc0_e == half_pi)
	{
		draw_list->PathArcToFast(ImVec2(x0, p1.y - rounding), rounding, 3, 6); // BL
		draw_list->PathArcToFast(ImVec2(x0, p0.y + rounding), rounding, 6, 9); // TR
	}
	else
	{
		draw_list->PathArcTo(ImVec2(x0, p1.y - rounding), rounding, 3.1415926f - arc0_e, 3.1415926f - arc0_b, 3); // BL
		draw_list->PathArcTo(ImVec2(x0, p0.y + rounding), rounding, 3.1415926f + arc0_b, 3.1415926f + arc0_e, 3); // TR
	}
	if (p1.x > rect.Min.x + rounding)
	{
		const float arc1_b = ImAcos01(1.0f - (rect.Max.x - p1.x) * inv_rounding);
		const float arc1_e = ImAcos01(1.0f - (rect.Max.x - p0.x) * inv_rounding);
		const float x1 = ImMin(p1.x, rect.Max.x - rounding);
		if (arc1_b == arc1_e)
		{
			draw_list->PathLineTo(ImVec2(x1, p0.y));
			draw_list->PathLineTo(ImVec2(x1, p1.y));
		}
		else if (arc1_b == 0.0f && arc1_e == half_pi)
		{
			draw_list->PathArcToFast(ImVec2(x1, p0.y + rounding), rounding, 9, 12); // TR
			draw_list->PathArcToFast(ImVec2(x1, p1.y - rounding), rounding, 0, 3); // BR
		}
		else
		{
			draw_list->PathArcTo(ImVec2(x1, p0.y + rounding), rounding, -arc1_e, -arc1_b, 3); // TR
			draw_list->PathArcTo(ImVec2(x1, p1.y - rounding), rounding, +arc1_b, +arc1_e, 3); // BR
		}
	}
	draw_list->PathFillConvex(col);
}

void ImGui::RenderColorRectWithAlphaCheckerboard(ImDrawList* draw_list, ImVec2 p_min, ImVec2 p_max, ImU32 col, float grid_step, ImVec2 grid_off, float rounding, int rounding_corners_flags)
{
	if (((col & IM_COL32_A_MASK) >> IM_COL32_A_SHIFT) < 0xFF)
	{
		ImU32 col_bg1 = ImGui::GetColorU32(ImAlphaBlendColors(IM_COL32(204, 204, 204, 255), col));
		ImU32 col_bg2 = ImGui::GetColorU32(ImAlphaBlendColors(IM_COL32(128, 128, 128, 255), col));
		draw_list->AddRectFilled(p_min, p_max, col_bg1, rounding, rounding_corners_flags);

		int yi = 0;
		for (float y = p_min.y + grid_off.y; y < p_max.y; y += grid_step, yi++)
		{
			float y1 = ImClamp(y, p_min.y, p_max.y), y2 = ImMin(y + grid_step, p_max.y);
			if (y2 <= y1)
				continue;
			for (float x = p_min.x + grid_off.x + (yi & 1) * grid_step; x < p_max.x; x += grid_step * 2.0f)
			{
				float x1 = ImClamp(x, p_min.x, p_max.x), x2 = ImMin(x + grid_step, p_max.x);
				if (x2 <= x1)
					continue;
				int rounding_corners_flags_cell = 0;
				if (y1 <= p_min.y) { if (x1 <= p_min.x) rounding_corners_flags_cell |= ImDrawCornerFlags_TopLeft; if (x2 >= p_max.x) rounding_corners_flags_cell |= ImDrawCornerFlags_TopRight; }
				if (y2 >= p_max.y) { if (x1 <= p_min.x) rounding_corners_flags_cell |= ImDrawCornerFlags_BotLeft; if (x2 >= p_max.x) rounding_corners_flags_cell |= ImDrawCornerFlags_BotRight; }
				rounding_corners_flags_cell &= rounding_corners_flags;
				draw_list->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col_bg2, rounding_corners_flags_cell ? rounding : 0.0f, rounding_corners_flags_cell);
			}
		}
	}
	else
	{
		draw_list->AddRectFilled(p_min, p_max, col, rounding, rounding_corners_flags);
	}
}

static unsigned int stb_decompress_length(const unsigned char *input)
{
	return (input[8] << 24) + (input[9] << 16) + (input[10] << 8) + input[11];
}

static unsigned char *stb__barrier_out_e, *stb__barrier_out_b;

static const unsigned char *stb__barrier_in_b;

static unsigned char *stb__dout;

static void stb__match(const unsigned char *data, unsigned int length)
{
	// INVERSE of memmove... write each byte before copying the next...
	if (stb__dout + length > stb__barrier_out_e) { stb__dout += length; return; }
	if (data < stb__barrier_out_b) { stb__dout = stb__barrier_out_e + 1; return; }
	while (length--) *stb__dout++ = *data++;
}

static void stb__lit(const unsigned char *data, unsigned int length)
{
	if (stb__dout + length > stb__barrier_out_e) { stb__dout += length; return; }
	if (data < stb__barrier_in_b) { stb__dout = stb__barrier_out_e + 1; return; }
	memcpy(stb__dout, data, length);
	stb__dout += length;
}

#define stb__in2(x) ((i[x] << 8) + i[(x)+1])
#define stb__in3(x) ((i[x] << 16) + stb__in2((x)+1))
#define stb__in4(x) ((i[x] << 24) + stb__in3((x)+1))

static const unsigned char *stb_decompress_token(const unsigned char *i)
{
	if (*i >= 0x20) { // use fewer if's for cases that expand small
		if (*i >= 0x80) stb__match(stb__dout - i[1] - 1, i[0] - 0x80 + 1), i += 2;
		else if (*i >= 0x40) stb__match(stb__dout - (stb__in2(0) - 0x4000 + 1), i[2] + 1), i += 3;
		else /* *i >= 0x20 */ stb__lit(i + 1, i[0] - 0x20 + 1), i += 1 + (i[0] - 0x20 + 1);
	}
	else { // more ifs for cases that expand large, since overhead is amortized
		if (*i >= 0x18) stb__match(stb__dout - (stb__in3(0) - 0x180000 + 1), i[3] + 1), i += 4;
		else if (*i >= 0x10) stb__match(stb__dout - (stb__in3(0) - 0x100000 + 1), stb__in2(3) + 1), i += 5;
		else if (*i >= 0x08) stb__lit(i + 2, stb__in2(0) - 0x0800 + 1), i += 2 + (stb__in2(0) - 0x0800 + 1);
		else if (*i == 0x07) stb__lit(i + 3, stb__in2(1) + 1), i += 3 + (stb__in2(1) + 1);
		else if (*i == 0x06) stb__match(stb__dout - (stb__in3(1) + 1), i[4] + 1), i += 5;
		else if (*i == 0x04) stb__match(stb__dout - (stb__in3(1) + 1), stb__in2(4) + 1), i += 6;
	}
	return i;
}

static unsigned int stb_adler32(unsigned int adler32, unsigned char *buffer, unsigned int buflen)
{
	const unsigned long ADLER_MOD = 65521;
	unsigned long s1 = adler32 & 0xffff, s2 = adler32 >> 16;
	unsigned long blocklen = buflen % 5552;

	unsigned long i;
	while (buflen) {
		for (i = 0; i + 7 < blocklen; i += 8) {
			s1 += buffer[0], s2 += s1;
			s1 += buffer[1], s2 += s1;
			s1 += buffer[2], s2 += s1;
			s1 += buffer[3], s2 += s1;
			s1 += buffer[4], s2 += s1;
			s1 += buffer[5], s2 += s1;
			s1 += buffer[6], s2 += s1;
			s1 += buffer[7], s2 += s1;

			buffer += 8;
		}

		for (; i < blocklen; ++i)
			s1 += *buffer++, s2 += s1;

		s1 %= ADLER_MOD, s2 %= ADLER_MOD;
		buflen -= blocklen;
		blocklen = 5552;
	}
	return (unsigned int)(s2 << 16) + (unsigned int)s1;
}

static unsigned int stb_decompress(unsigned char *output, const unsigned char *i, unsigned int /*length*/)
{
	if (stb__in4(0) != 0x57bC0000) return 0;
	if (stb__in4(4) != 0) return 0;
	const unsigned int olen = stb_decompress_length(i);
	stb__barrier_in_b = i;
	stb__barrier_out_e = output + olen;
	stb__barrier_out_b = output;
	i += 16;

	stb__dout = output;
	for (;;) {
		const unsigned char *old_i = i;
		i = stb_decompress_token(i);
		if (i == old_i) {
			if (*i == 0x05 && i[1] == 0xfa) {
				if (stb__dout != output + olen) return 0;
				if (stb_adler32(1, output, olen) != (unsigned int)stb__in4(2))
					return 0;
				return olen;
			}
			else {
				return 0;
			}
		}
		if (stb__dout > output + olen)
			return 0;
	}
}