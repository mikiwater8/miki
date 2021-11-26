#pragma once

#include <float.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>


/*
// Helper Macros
#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR)            assert(_EXPR)                               // You can override the default assert handler by editing imconfig.h
#endif
#if defined(__clang__) || defined(__GNUC__)
#define IM_FMTARGS(FMT)             __attribute__((format(printf, FMT, FMT+1))) // Apply printf-style warnings to user functions.
#define IM_FMTLIST(FMT)             __attribute__((format(printf, FMT, 0)))
#else
#define IM_FMTARGS(FMT)
#define IM_FMTLIST(FMT)
#endif
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))         // Size of a static C-style array. Don't use on pointers!
#define IM_OFFSETOF(_TYPE,_MEMBER)  ((size_t)&(((_TYPE*)0)->_MEMBER))           // Offset of _MEMBER within _TYPE. Standardized as offsetof() in modern C++.
#define IM_UNUSED(_VAR)             ((void)_VAR)                                // Used to silence "unused variable warnings". Often useful as asserts may be stripped out from final builds.*/

struct ImDrawChannel; // Temporary storage to output draw commands out of order, used by ImDrawListSplitter and ImDrawList::ChannelsSplit()
struct ImDrawCmd; // A single draw command within a parent ImDrawList (generally maps to 1 GPU draw call, unless it is a callback)
struct ImDrawData; // All draw command lists required to render the frame + pos/size coordinates to use for the projection matrix.
struct ImDrawList; // A single draw command list (generally one per window, conceptually you may see this as a dynamic "mesh" builder)
struct ImDrawListSharedData; // Data shared among multiple draw lists (typically owned by parent ImGui context, but you may create one yourself)
struct ImDrawListSplitter; // Helper to split a draw list into different layers which can be drawn into out of order, then flattened back.
struct ImDrawVert; // A single vertex (pos + uv + col = 20 bytes by default. Override layout with IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT)
struct ImFont; // Runtime data for a single font within a parent ImFontAtlas
struct ImFontAtlas; // Runtime data for multiple fonts, bake multiple fonts into a single texture, TTF/OTF font loader
struct ImFontConfig; // Configuration data when adding a font or merging fonts
struct ImFontGlyph; // A single font glyph (code point + coordinates within in ImFontAtlas + offset)
struct ImFontGlyphRangesBuilder; // Helper to build glyph ranges from text/string data
struct ImColor; // Helper functions to create a color that can be converted to either u32 or float4 (*OBSOLETE* please avoid using)
struct ImGuiContext; // Dear ImGui context (opaque structure, unless including imgui_internal.h)
struct ImGuiIO; // Main configuration and I/O between your application and ImGui
struct ImGuiInputTextCallbackData; // Shared state of InputText() when using custom ImGuiInputTextCallback (rare/advanced use)
struct ImGuiListClipper; // Helper to manually clip large list of items
struct ImGuiOnceUponAFrame; // Helper for running a block of code not more than once a frame, used by IMGUI_ONCE_UPON_A_FRAME macro
struct ImGuiPayload; // User data payload for drag and drop operations
struct ImGuiSizeCallbackData; // Callback data when using SetNextWindowSizeConstraints() (rare/advanced use)
struct ImGuiStorage; // Helper for key->value storage
struct ImGuiStyle; // Runtime data for styling/colors
struct ImGuiTextBuffer; // Helper to hold and append into a text buffer (~string builder)
struct ImGuiTextFilter; // Helper to parse and apply text filters (e.g. "aaaaa[,bbbbb][,ccccc]")

typedef int ImGuiCol; // -> enum ImGuiCol_ // Enum: A color identifier for styling
typedef int ImGuiCond; // -> enum ImGuiCond_ // Enum: A condition for many Set*() functions
typedef int ImGuiDataType; // -> enum ImGuiDataType_ // Enum: A primary data type
typedef int ImGuiDir; // -> enum ImGuiDir_ // Enum: A cardinal direction
typedef int ImGuiKey; // -> enum ImGuiKey_ // Enum: A key identifier (ImGui-side enum)
typedef int ImGuiNavInput; // -> enum ImGuiNavInput_ // Enum: An input identifier for navigation
typedef int ImGuiMouseButton; // -> enum ImGuiMouseButton_ // Enum: A mouse button identifier (0=left, 1=right, 2=middle)
typedef int ImGuiMouseCursor; // -> enum ImGuiMouseCursor_ // Enum: A mouse cursor identifier
typedef int ImGuiStyleVar; // -> enum ImGuiStyleVar_ // Enum: A variable identifier for styling
typedef int ImDrawCornerFlags; // -> enum ImDrawCornerFlags_ // Flags: for ImDrawList::AddRect(), AddRectFilled() etc.
typedef int ImDrawListFlags; // -> enum ImDrawListFlags_ // Flags: for ImDrawList
typedef int ImFontAtlasFlags; // -> enum ImFontAtlasFlags_ // Flags: for ImFontAtlas
typedef int ImGuiBackendFlags; // -> enum ImGuiBackendFlags_ // Flags: for io.BackendFlags
typedef int ImGuiColorEditFlags; // -> enum ImGuiColorEditFlags_ // Flags: for ColorEdit4(), ColorPicker4() etc.
typedef int ImGuiConfigFlags; // -> enum ImGuiConfigFlags_ // Flags: for io.ConfigFlags
typedef int ImGuiComboFlags; // -> enum ImGuiComboFlags_ // Flags: for BeginCombo()
typedef int ImGuiDragDropFlags; // -> enum ImGuiDragDropFlags_ // Flags: for BeginDragDropSource(), AcceptDragDropPayload()
typedef int ImGuiFocusedFlags; // -> enum ImGuiFocusedFlags_ // Flags: for IsWindowFocused()
typedef int ImGuiHoveredFlags; // -> enum ImGuiHoveredFlags_ // Flags: for IsItemHovered(), IsWindowHovered() etc.
typedef int ImGuiInputTextFlags; // -> enum ImGuiInputTextFlags_ // Flags: for InputText(), InputTextMultiline()
typedef int ImGuiKeyModFlags; // -> enum ImGuiKeyModFlags_ // Flags: for io.KeyMods (Ctrl/Shift/Alt/Super)
typedef int ImGuiSelectableFlags; // -> enum ImGuiSelectableFlags_ // Flags: for Selectable()
typedef int ImGuiTabBarFlags; // -> enum ImGuiTabBarFlags_ // Flags: for BeginTabBar()
typedef int ImGuiTabItemFlags; // -> enum ImGuiTabItemFlags_ // Flags: for BeginTabItem()
typedef int ImGuiTreeNodeFlags; // -> enum ImGuiTreeNodeFlags_ // Flags: for TreeNode(), TreeNodeEx(), CollapsingHeader()
typedef int ImGuiWindowFlags; // -> enum ImGuiWindowFlags_ // Flags: for Begin(), BeginChild()
typedef void* ImTextureID; // User data for rendering back-end to identify a texture. This is whatever to you want it to be! read the FAQ about ImTextureID for details.
typedef unsigned int ImGuiID; // A unique ID used by widgets, typically hashed from a stack of string.
typedef int(*ImGuiInputTextCallback)(ImGuiInputTextCallbackData *data);
typedef void(*ImGuiSizeCallback)(ImGuiSizeCallbackData* data);

typedef unsigned short ImWchar16; // A single decoded U16 character/code point. We encode them as multi bytes UTF-8 when used in strings.
typedef unsigned int ImWchar32; // A single decoded U32 character/code point. We encode them as multi bytes UTF-8 when used in strings.
typedef ImWchar16 ImWchar;

typedef signed char ImS8; // 8-bit signed integer
typedef unsigned char ImU8; // 8-bit unsigned integer
typedef signed short ImS16; // 16-bit signed integer
typedef unsigned short ImU16; // 16-bit unsigned integer
typedef signed int ImS32; // 32-bit signed integer == int
typedef unsigned int ImU32; // 32-bit unsigned integer (often used to store packed colors)
typedef signed __int64 ImS64; // 64-bit signed integer (pre and post C++11 with Visual Studio)
typedef unsigned __int64 ImU64; // 64-bit unsigned integer (pre and post C++11 with Visual Studio)

struct ImVec2
{
	float x, y;
	ImVec2() { x = y = 0.0f; }
	ImVec2(float _x, float _y) { x = _x; y = _y; }
	float operator[] (size_t idx) const { return (&x)[idx]; } // We very rarely use this [] operator, the assert overhead is fine.
	float& operator[] (size_t idx) { return (&x)[idx]; } // We very rarely use this [] operator, the assert overhead is fine.
};

struct ImVec4
{
	float x, y, z, w;
	ImVec4() { x = y = z = w = 0.0f; }
	ImVec4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
};

namespace ImGui
{
	ImGuiContext* CreateContext(ImFontAtlas* shared_font_atlas = NULL);
	void DestroyContext(ImGuiContext* ctx = NULL);
	ImGuiContext* GetCurrentContext();
	void SetCurrentContext(ImGuiContext* ctx);
	ImGuiIO& GetIO();
	ImGuiStyle& GetStyle();
	void NewFrame();
	void EndFrame();
	void Render();
	ImDrawData* GetDrawData();
	void StyleColorsDark(ImGuiStyle* dst = NULL);
	bool Begin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
	void End();
	bool BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);
	bool BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);
	void EndChild();
	bool IsWindowAppearing();
	bool IsWindowCollapsed();
	bool IsWindowFocused(ImGuiFocusedFlags flags = 0);
	bool IsWindowHovered(ImGuiHoveredFlags flags = 0);
	ImDrawList* GetWindowDrawList();
	ImVec2 GetWindowPos();
	ImVec2 GetWindowSize();
	float GetWindowWidth();
	float GetWindowHeight();
	void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2& pivot = ImVec2(0, 0));
	void SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);
	void SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = NULL, void* custom_callback_data = NULL);
	void SetNextWindowContentSize(const ImVec2& size);
	void SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
	void SetNextWindowFocus();
	void SetNextWindowBgAlpha(float alpha);
	void SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0);
	void SetWindowSize(const ImVec2& size, ImGuiCond cond = 0);
	void SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
	void SetWindowFocus();
	void SetWindowFontScale(float scale);
	void SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0);
	void SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0);
	void SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0);
	void SetWindowFocus(const char* name);
	ImVec2 GetContentRegionMax();
	ImVec2 GetContentRegionAvail();
	ImVec2 GetWindowContentRegionMin();
	ImVec2 GetWindowContentRegionMax();
	float GetWindowContentRegionWidth();
	float GetScrollX();
	float GetScrollY();
	float GetScrollMaxX();
	float GetScrollMaxY();
	void SetScrollX(float scroll_x);
	void SetScrollY(float scroll_y);
	void SetScrollHereX(float center_x_ratio = 0.5f);
	void SetScrollHereY(float center_y_ratio = 0.5f);
	void SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);
	void SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);
	void PushFont(ImFont* font);
	void PopFont();
	void PushStyleColor(ImGuiCol idx, ImU32 col);
	void PushStyleColor(ImGuiCol idx, const ImVec4& col);
	void PopStyleColor(int count = 1);
	void PushStyleVar(ImGuiStyleVar idx, float val);
	void PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
	void PopStyleVar(int count = 1);
	const ImVec4& GetStyleColorVec4(ImGuiCol idx);
	ImFont* GetFont();
	float GetFontSize();
	ImVec2 GetFontTexUvWhitePixel();
	ImU32 GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);
	ImU32 GetColorU32(const ImVec4& col);
	ImU32 GetColorU32(ImU32 col);
	void PushItemWidth(float item_width);
	void PopItemWidth();
	void SetNextItemWidth(float item_width);
	float CalcItemWidth();
	void PushTextWrapPos(float wrap_local_pos_x = 0.0f);
	void PopTextWrapPos();
	void PushAllowKeyboardFocus(bool allow_keyboard_focus);
	void PopAllowKeyboardFocus();
	void PushButtonRepeat(bool repeat);
	void PopButtonRepeat();
	void Separator();
	void SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);
	void NewLine();
	void Spacing();
	void Dummy(const ImVec2& size);
	void Indent(float indent_w = 0.0f); // move content position toward the right, by style.IndentSpacing or indent_w if != 0
	void Unindent(float indent_w = 0.0f); // move content position back to the left, by style.IndentSpacing or indent_w if != 0
	void BeginGroup(); // lock horizontal starting position
	void EndGroup(); // unlock horizontal starting position + capture the whole group bounding box into one "item" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)
	ImVec2 GetCursorPos(); // cursor position in window coordinates (relative to window position)
	float GetCursorPosX(); // (some functions are using window-relative coordinates, such as: GetCursorPos, GetCursorStartPos, GetContentRegionMax, GetWindowContentRegion* etc.
	float GetCursorPosY(); // other functions such as GetCursorScreenPos or everything in ImDrawList::
	void SetCursorPos(const ImVec2& local_pos); // are using the main, absolute coordinate system.
	void SetCursorPosX(float local_x); // GetWindowPos() + GetCursorPos() == GetCursorScreenPos() etc.)
	void SetCursorPosY(float local_y); //
	ImVec2 GetCursorStartPos(); // initial cursor position in window coordinates
	ImVec2 GetCursorScreenPos(); // cursor position in absolute screen coordinates [0..io.DisplaySize] (useful to work with ImDrawList API)
	void SetCursorScreenPos(const ImVec2& pos); // cursor position in absolute screen coordinates [0..io.DisplaySize]
	void AlignTextToFramePadding(); // vertically align upcoming text baseline to FramePadding.y so that it will align properly to regularly framed items (call if you have text on a line before a framed item)
	float GetTextLineHeight(); // ~ FontSize
	float GetTextLineHeightWithSpacing(); // ~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)
	float GetFrameHeight(); // ~ FontSize + style.FramePadding.y * 2
	float GetFrameHeightWithSpacing(); // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)
	void PushID(const char* str_id); // push string into the ID stack (will hash string).
	void PushID(const char* str_id_begin, const char* str_id_end); // push string into the ID stack (will hash string).
	void PushID(const void* ptr_id); // push pointer into the ID stack (will hash pointer).
	void PushID(int int_id); // push integer into the ID stack (will hash integer).
	void PopID(); // pop from the ID stack.
	ImGuiID GetID(const char* str_id); // calculate unique ID (hash of whole ID stack + given parameter). e.g. if you want to query into ImGuiStorage yourself
	ImGuiID GetID(const char* str_id_begin, const char* str_id_end);
	ImGuiID GetID(const void* ptr_id);
	void TextUnformatted(const char* text, const char* text_end = NULL); // raw text without formatting. Roughly equivalent to Text("%s", text) but: A) doesn't require null terminated string if 'text_end' is specified, B) it's faster, no memory copy is done, no buffer size limits, recommended for long chunks of text.
	void Text(const char* fmt, ...); // formatted text
	void TextV(const char* fmt, va_list args);
	void TextColored(const ImVec4& col, const char* fmt, ...); // shortcut for PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor();
	void TextColoredV(const ImVec4& col, const char* fmt, va_list args);
	void TextDisabled(const char* fmt, ...); // shortcut for PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
	void TextDisabledV(const char* fmt, va_list args);
	void TextWrapped(const char* fmt, ...); // shortcut for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. Note that this won't work on an auto-resizing window if there's no other widgets to extend the window width, yoy may need to set a size using SetNextWindowSize().
	void TextWrappedV(const char* fmt, va_list args);
	void LabelText(const char* label, const char* fmt, ...); // display text+label aligned the same way as value+label widgets
	void LabelTextV(const char* label, const char* fmt, va_list args);
	void BulletText(const char* fmt, ...); // shortcut for Bullet()+Text()
	void BulletTextV(const char* fmt, va_list args);
	bool Button(const char* label, const ImVec2& size = ImVec2(0, 0)); // button
	bool SmallButton(const char* label); // button with FramePadding=(0,0) to easily embed within text
	bool InvisibleButton(const char* str_id, const ImVec2& size); // button behavior without the visuals, frequently useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)
	bool ArrowButton(const char* str_id, ImGuiDir dir); // square button with an arrow shape
	void Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
	bool ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1)); // <0 frame_padding uses default frame padding settings. 0 for no padding
	bool Checkbox(const char* label, bool* v);
	bool CheckboxEx(const char* label, bool* v);
	bool CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
	bool RadioButton(const char* label, bool active); // use with e.g. if (RadioButton("one", my_value==1)) { my_value = 1; }
	bool RadioButton(const char* label, int* v, int v_button); // shortcut to handle the above pattern when value is an integer
	void ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-1, 0), const char* overlay = NULL);
	void Bullet(); // draw a small circle and keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses
	bool BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
	void EndCombo(); // only call EndCombo() if BeginCombo() returns true!
	bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
	bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1); // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
	bool Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);
	bool DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f); // If v_min >= v_max we have no bound
	bool DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	bool DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	bool DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	bool DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, float power = 1.0f);
	bool DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d"); // If v_min >= v_max we have no bound
	bool DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	bool DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	bool DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	bool DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = NULL);
	bool DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, float power = 1.0f);
	bool DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, float power = 1.0f);
	bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f); // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display. Use power!=1.0 for power curve sliders
	bool SliderFloatEx(const char* label, float* v, float v_min, float v_max, const char* display_format, float power, ImVec2 size, ImVec4 color);
	bool SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	bool SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	bool SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	bool SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg");
	bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d");
	bool SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d");
	bool SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d");
	bool SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d");
	bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, float power = 1.0f);
	bool SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = NULL, float power = 1.0f);
	bool VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	bool VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format = "%d");
	bool VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, float power = 1.0f);
	bool InputData(const char* label, char* buf, ...);
	bool InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
	bool InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
	bool InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
	bool InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
	bool InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
	bool InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
	bool InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
	bool InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
	bool InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0);
	bool InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0);
	bool InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0);
	bool InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
	bool InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
	bool InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
	bool ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 32);
	bool ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 32);
	bool ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
	bool ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
	bool ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0)); // display a colored square/button, hover for details, return true when pressed.
	void SetColorEditOptions(ImGuiColorEditFlags flags); // initialize current options (generally on application startup) if you want to select a default format, picker type, etc. User will be able to change many settings, unless you pass the _NoOptions flag to your calls.
	bool TreeNode(const char* label);
	bool TreeNode(const char* str_id, const char* fmt, ...); // helper variation to easily decorelate the id from the displayed string. Read the FAQ about why and how to use ID. to align arbitrary text at the same level as a TreeNode() you can use Bullet().
	bool TreeNode(const void* ptr_id, const char* fmt, ...); // "
	bool TreeNodeV(const char* str_id, const char* fmt, va_list args);
	bool TreeNodeV(const void* ptr_id, const char* fmt, va_list args);
	bool TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
	bool TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...);
	bool TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...);
	bool TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args);
	bool TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args);
	void TreePush(const char* str_id); // ~ Indent()+PushId(). Already called by TreeNode() when returning true, but you can call TreePush/TreePop yourself if desired.
	void TreePush(const void* ptr_id = NULL); // "
	void TreePop(); // ~ Unindent()+PopId()
	float GetTreeNodeToLabelSpacing(); // horizontal distance preceding label when using TreeNode*() or Bullet() == (g.FontSize + style.FramePadding.x*2) for a regular unframed TreeNode
	bool CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0); // if returning 'true' the header is open. doesn't indent nor push on ID stack. user doesn't have to call TreePop().
	bool CollapsingHeader(const char* label, bool* p_open, ImGuiTreeNodeFlags flags = 0); // when 'p_open' isn't NULL, display an additional small close button on upper right of the header
	void SetNextItemOpen(bool is_open, ImGuiCond cond = 0); // set next TreeNode/CollapsingHeader open state.
	bool Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
	bool Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // "bool* p_selected" point to the selection state (read-write), as a convenient helper.
	bool ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
	bool ListBox(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
	bool ListBoxHeader(const char* label, const ImVec2& size = ImVec2(0, 0)); // use if you want to reimplement ListBox() will custom data or interactions. if the function return true, you can output elements then call ListBoxFooter() afterwards.
	bool ListBoxHeader(const char* label, int items_count, int height_in_items = -1); // "
	void ListBoxFooter(); // terminate the scrolling region. only call ListBoxFooter() if ListBoxHeader() returned true!
	void PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
	void PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
	void PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
	void PlotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
	void Value(const char* prefix, bool b);
	void Value(const char* prefix, int v);
	void Value(const char* prefix, unsigned int v);
	void Value(const char* prefix, float v, const char* float_format = NULL);
	bool BeginMenuBar(); // append to menu-bar of current window (requires ImGuiWindowFlags_MenuBar flag set on parent window).
	void EndMenuBar(); // only call EndMenuBar() if BeginMenuBar() returns true!
	bool BeginMainMenuBar(); // create and append to a full screen menu-bar.
	void EndMainMenuBar(); // only call EndMainMenuBar() if BeginMainMenuBar() returns true!
	bool BeginMenu(const char* label, bool enabled = true); // create a sub-menu entry. only call EndMenu() if this returns true!
	void EndMenu(); // only call EndMenu() if BeginMenu() returns true!
	bool MenuItem(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true); // return true when activated. shortcuts are displayed for convenience but not processed by ImGui at the moment
	bool MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true); // return true when activated + toggle (*p_selected) if p_selected != NULL
	void BeginTooltip(); // begin/append a tooltip window. to create full-featured tooltip (with any kind of items).
	void EndTooltip();
	void SetTooltip(const char* fmt, ...); // set a text-only tooltip, typically use with ImGui::IsItemHovered(). override any previous call to SetTooltip().
	void SetTooltipV(const char* fmt, va_list args);
	void OpenPopup(const char* str_id); // call to mark popup as open (don't call every frame!). popups are closed when user click outside, or if CloseCurrentPopup() is called within a BeginPopup()/EndPopup() block. By default, Selectable()/MenuItem() are calling CloseCurrentPopup(). Popup identifiers are relative to the current ID-stack (so OpenPopup and BeginPopup needs to be at the same level).
	bool BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0); // return true if the popup is open, and you can start outputting to it. only call EndPopup() if BeginPopup() returns true!
	bool BeginPopupContextItem(const char* str_id = NULL, ImGuiMouseButton mouse_button = 1); // helper to open and begin popup when clicked on last item. if you can pass a NULL str_id only if the previous item had an id. If you want to use that on a non-interactive item such as Text() you need to pass in an explicit ID here. read comments in .cpp!
	bool BeginPopupContextWindow(const char* str_id = NULL, ImGuiMouseButton mouse_button = 1, bool also_over_items = true); // helper to open and begin popup when clicked on current window.
	bool BeginPopupContextVoid(const char* str_id = NULL, ImGuiMouseButton mouse_button = 1); // helper to open and begin popup when clicked in void (where there are no imgui windows).
	bool BeginPopupModal(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0); // modal dialog (regular window with title bar, block interactions behind the modal window, can't close the modal window by clicking outside)
	void EndPopup(); // only call EndPopup() if BeginPopupXXX() returns true!
	bool OpenPopupOnItemClick(const char* str_id = NULL, ImGuiMouseButton mouse_button = 1); // helper to open popup when clicked on last item (note: actually triggers on the mouse _released_ event to be consistent with popup behaviors). return true when just opened.
	bool IsPopupOpen(const char* str_id); // return true if the popup is open at the current begin-ed level of the popup stack.
	void CloseCurrentPopup(); // close the popup we have begin-ed into. clicking on a MenuItem or Selectable automatically close the current popup.
	void Columns(int count = 1, const char* id = NULL, bool border = true);
	void NextColumn(); // next column, defaults to current row or next row if the current row is finished
	int GetColumnIndex(); // get current column index
	float GetColumnWidth(int column_index = -1); // get column width (in pixels). pass -1 to use current column
	void SetColumnWidth(int column_index, float width); // set column width (in pixels). pass -1 to use current column
	float GetColumnOffset(int column_index = -1); // get position of column line (in pixels, from the left side of the contents region). pass -1 to use current column, otherwise 0..GetColumnsCount() inclusive. column 0 is typically 0.0f
	void SetColumnOffset(int column_index, float offset_x); // set position of column line (in pixels, from the left side of the contents region). pass -1 to use current column
	int GetColumnsCount();
	bool BeginTabBar(const char* str_id, ImGuiTabBarFlags flags = 0); // create and append into a TabBar
	void EndTabBar(); // only call EndTabBar() if BeginTabBar() returns true!
	bool BeginTabItem(const char* label, bool* p_open = NULL, ImGuiTabItemFlags flags = 0);// create a Tab. Returns true if the Tab is selected.
	void EndTabItem(); // only call EndTabItem() if BeginTabItem() returns true!
	void SetTabItemClosed(const char* tab_or_docked_window_label); // notify TabBar or Docking system of a closed tab/window ahead (useful to reduce visual flicker on reorderable tab bars). For tab-bar: call after BeginTabBar() and before Tab submissions. Otherwise call with a window name.
	bool BeginDragDropSource(ImGuiDragDropFlags flags = 0); // call when the current item is active. If this return true, you can call SetDragDropPayload() + EndDragDropSource()
	bool SetDragDropPayload(const char* type, const void* data, size_t sz, ImGuiCond cond = 0); // type is a user defined string of maximum 32 characters. Strings starting with '_' are reserved for dear imgui internal types. Data is copied and held by imgui.
	void EndDragDropSource(); // only call EndDragDropSource() if BeginDragDropSource() returns true!
	bool BeginDragDropTarget(); // call after submitting an item that may receive a payload. If this returns true, you can call AcceptDragDropPayload() + EndDragDropTarget()
	const ImGuiPayload* AcceptDragDropPayload(const char* type, ImGuiDragDropFlags flags = 0); // accept contents of a given type. If ImGuiDragDropFlags_AcceptBeforeDelivery is set you can peek into the payload before the mouse button is released.
	void EndDragDropTarget(); // only call EndDragDropTarget() if BeginDragDropTarget() returns true!
	const ImGuiPayload* GetDragDropPayload(); // peek directly into the current payload from anywhere. may return NULL. use ImGuiPayload::IsDataType() to test for the payload type.
	void PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
	void PopClipRect();
	void SetItemDefaultFocus(); // make last item the default focused item of a window.
	void SetKeyboardFocusHere(int offset = 0); // focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget. Use -1 to access previous widget.
	bool IsItemHovered(ImGuiHoveredFlags flags = 0); // is the last item hovered? (and usable, aka not blocked by a popup, etc.). See ImGuiHoveredFlags for more options.
	bool IsItemActive(); // is the last item active? (e.g. button being held, text field being edited. This will continuously return true while holding mouse button on an item. Items that don't interact will always return false)
	bool IsItemFocused(); // is the last item focused for keyboard/gamepad navigation?
	bool IsItemClicked(ImGuiMouseButton mouse_button = 0); // is the last item clicked? (e.g. button/node just clicked on) == IsMouseClicked(mouse_button) && IsItemHovered()
	bool IsItemVisible(); // is the last item visible? (items may be out of sight because of clipping/scrolling)
	bool IsItemEdited(); // did the last item modify its underlying value this frame? or was pressed? This is generally the same as the "bool" return value of many widgets.
	bool IsItemActivated(); // was the last item just made active (item was previously inactive).
	bool IsItemDeactivated(); // was the last item just made inactive (item was previously active). Useful for Undo/Redo patterns with widgets that requires continuous editing.
	bool IsItemDeactivatedAfterEdit(); // was the last item just made inactive and made a value change when it was active? (e.g. Slider/Drag moved). Useful for Undo/Redo patterns with widgets that requires continuous editing. Note that you may get false positives (some widgets such as Combo()/ListBox()/Selectable() will return true even when clicking an already selected item).
	bool IsItemToggledOpen(); // was the last item open state toggled? set by TreeNode().
	bool IsAnyItemHovered(); // is any item hovered?
	bool IsAnyItemActive(); // is any item active?
	bool IsAnyItemFocused(); // is any item focused?
	ImVec2 GetItemRectMin(); // get upper-left bounding rectangle of the last item (screen space)
	ImVec2 GetItemRectMax(); // get lower-right bounding rectangle of the last item (screen space)
	ImVec2 GetItemRectSize(); // get size of last item
	void SetItemAllowOverlap(); // allow last item to be overlapped by a subsequent item. sometimes useful with invisible buttons, selectables, etc. to catch unused area.
	bool IsRectVisible(const ImVec2& size); // test if rectangle (of given size, starting from cursor position) is visible / not clipped.
	bool IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max); // test if rectangle (in screen space) is visible / not clipped. to perform coarse clipping on user's side.
	double GetTime(); // get global imgui time. incremented by io.DeltaTime every frame.
	int GetFrameCount(); // get global imgui frame count. incremented by 1 every frame.
	ImDrawList* GetBackgroundDrawList(); // this draw list will be the first rendering one. Useful to quickly draw shapes/text behind dear imgui contents.
	ImDrawList* GetForegroundDrawList(); // this draw list will be the last rendered one. Useful to quickly draw shapes/text over dear imgui contents.
	ImDrawListSharedData* GetDrawListSharedData(); // you may use this when creating your own ImDrawList instances.
	void SetStateStorage(ImGuiStorage* storage); // replace current window storage with our own (if you want to manipulate it yourself, typically clear subsection of it)
	ImGuiStorage* GetStateStorage();
	void CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end); // calculate coarse clipping for large list of evenly sized items. Prefer using the ImGuiListClipper higher-level helper if you can.
	bool BeginChildFrame(ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0); // helper to create a child window / scrolling region that looks like a normal widget frame
	void EndChildFrame(); // always call EndChildFrame() regardless of BeginChildFrame() return values (which indicates a collapsed/clipped window)
	ImVec2 CalcTextSize(const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
	ImVec4 ColorConvertU32ToFloat4(ImU32 in);
	ImU32 ColorConvertFloat4ToU32(const ImVec4& in);
	void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
	void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);
	int GetKeyIndex(ImGuiKey imgui_key); // map ImGuiKey_* values into user's key index. == io.KeyMap[key]
	bool IsKeyDown(int user_key_index); // is key being held. == io.KeysDown[user_key_index].
	bool IsKeyPressed(int user_key_index, bool repeat = true); // was key pressed (went from !Down to Down)? if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate
	bool IsKeyReleased(int user_key_index); // was key released (went from Down to !Down)?
	int GetKeyPressedAmount(int key_index, float repeat_delay, float rate); // uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate
	void CaptureKeyboardFromApp(bool want_capture_keyboard_value = true); // attention: misleading name! manually override io.WantCaptureKeyboard flag next frame (said flag is entirely left for your application to handle). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting "io.WantCaptureKeyboard = want_capture_keyboard_value"; after the next NewFrame() call.
	bool IsMouseDown(ImGuiMouseButton button); // is mouse button held?
	bool IsMouseClicked(ImGuiMouseButton button, bool repeat = false); // did mouse button clicked? (went from !Down to Down)
	bool IsMouseReleased(ImGuiMouseButton button); // did mouse button released? (went from Down to !Down)
	bool IsMouseDoubleClicked(ImGuiMouseButton button); // did mouse button double-clicked? a double-click returns false in IsMouseClicked(). uses io.MouseDoubleClickTime.
	bool IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);// is mouse hovering given bounding rect (in screen space). clipped by current clipping settings, but disregarding of other consideration of focus/window ordering/popup-block.
	bool IsMousePosValid(const ImVec2* mouse_pos = NULL); // by convention we use (-FLT_MAX,-FLT_MAX) to denote that there is no mouse available
	bool IsAnyMouseDown(); // is any mouse button held?
	ImVec2 GetMousePos(); // shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls
	ImVec2 GetMousePosOnOpeningCurrentPopup(); // retrieve mouse position at the time of opening popup we have BeginPopup() into (helper to avoid user backing that value themselves)
	bool IsMouseDragging(ImGuiMouseButton button, float lock_threshold = -1.0f); // is mouse dragging? (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)
	ImVec2 GetMouseDragDelta(ImGuiMouseButton button = 0, float lock_threshold = -1.0f); // return the delta from the initial clicking position while the mouse button is pressed or was just released. This is locked and return 0.0f until the mouse moves past a distance threshold at least once (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)
	void ResetMouseDragDelta(ImGuiMouseButton button = 0); //
	ImGuiMouseCursor GetMouseCursor(); // get desired cursor type, reset in ImGui::NewFrame(), this is updated during the frame. valid before Render(). If you use software rendering by setting io.MouseDrawCursor ImGui will render those for you
	void SetMouseCursor(ImGuiMouseCursor cursor_type); // set desired cursor type
	void CaptureMouseFromApp(bool want_capture_mouse_value = true); // attention: misleading name! manually override io.WantCaptureMouse flag next frame (said flag is entirely left for your application to handle). This is equivalent to setting "io.WantCaptureMouse = want_capture_mouse_value;" after the next NewFrame() call.
	const char* GetClipboardText();
	void SetClipboardText(const char* text);
	void* MemAlloc(size_t size);
	void MemFree(void* ptr);
	bool HotKey(const char* label, int* k);
	void HelpMarker(const char* desc, ...);
}

enum ImGuiWindowFlags_
{
	ImGuiWindowFlags_None = 0,
	ImGuiWindowFlags_NoTitleBar = 1 << 0, // Disable title-bar
	ImGuiWindowFlags_NoResize = 1 << 1, // Disable user resizing with the lower-right grip
	ImGuiWindowFlags_NoMove = 1 << 2, // Disable user moving the window
	ImGuiWindowFlags_NoScrollbar = 1 << 3, // Disable scrollbars (window can still scroll with mouse or programmatically)
	ImGuiWindowFlags_NoScrollWithMouse = 1 << 4, // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
	ImGuiWindowFlags_NoCollapse = 1 << 5, // Disable user collapsing window by double-clicking on it
	ImGuiWindowFlags_AlwaysAutoResize = 1 << 6, // Resize every window to its content every frame
	ImGuiWindowFlags_NoBackground = 1 << 7, // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
	ImGuiWindowFlags_NoSavedSettings = 1 << 8, // Never load/save settings in .ini file
	ImGuiWindowFlags_NoMouseInputs = 1 << 9, // Disable catching mouse, hovering test with pass through.
	ImGuiWindowFlags_MenuBar = 1 << 10, // Has a menu-bar
	ImGuiWindowFlags_HorizontalScrollbar = 1 << 11, // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
	ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12, // Disable taking focus when transitioning from hidden to visible state
	ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13, // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
	ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14, // Always show vertical scrollbar (even if ContentSize.y < Size.y)
	ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15, // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
	ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16, // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
	ImGuiWindowFlags_NoNavInputs = 1 << 18, // No gamepad/keyboard navigation within the window
	ImGuiWindowFlags_NoNavFocus = 1 << 19, // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
	ImGuiWindowFlags_UnsavedDocument = 1 << 20, // Append '*' to title without affecting the ID, as a convenience to avoid using the ### operator. When used in a tab/docking context, tab is selected on closure and closure is deferred by one frame to allow code to cancel the closure (with a confirmation popup, etc.) without flicker.
	ImGuiWindowFlags_NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
	ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
	ImGuiWindowFlags_NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,

	// [Internal]
	ImGuiWindowFlags_NavFlattened = 1 << 23, // [BETA] Allow gamepad/keyboard navigation to cross over parent border to this child (only use on child that have no scrolling!)
	ImGuiWindowFlags_ChildWindow = 1 << 24, // Don't use! For internal use by BeginChild()
	ImGuiWindowFlags_Tooltip = 1 << 25, // Don't use! For internal use by BeginTooltip()
	ImGuiWindowFlags_Popup = 1 << 26, // Don't use! For internal use by BeginPopup()
	ImGuiWindowFlags_Modal = 1 << 27, // Don't use! For internal use by BeginPopupModal()
	ImGuiWindowFlags_ChildMenu = 1 << 28 // Don't use! For internal use by BeginMenu()

	// [Obsolete]
	//ImGuiWindowFlags_ShowBorders = 1 << 7, // --> Set style.FrameBorderSize=1.0f or style.WindowBorderSize=1.0f to enable borders around items or windows.
	//ImGuiWindowFlags_ResizeFromAnySide = 1 << 17, // --> Set io.ConfigWindowsResizeFromEdges=true and make sure mouse cursors are supported by back-end (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)
};

enum ImGuiInputTextFlags_
{
	ImGuiInputTextFlags_None = 0,
	ImGuiInputTextFlags_CharsDecimal = 1 << 0, // Allow 0123456789.+-*/
	ImGuiInputTextFlags_CharsHexadecimal = 1 << 1, // Allow 0123456789ABCDEFabcdef
	ImGuiInputTextFlags_CharsUppercase = 1 << 2, // Turn a..z into A..Z
	ImGuiInputTextFlags_CharsNoBlank = 1 << 3, // Filter out spaces, tabs
	ImGuiInputTextFlags_AutoSelectAll = 1 << 4, // Select entire text when first taking mouse focus
	ImGuiInputTextFlags_EnterReturnsTrue = 1 << 5, // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
	ImGuiInputTextFlags_CallbackCompletion = 1 << 6, // Callback on pressing TAB (for completion handling)
	ImGuiInputTextFlags_CallbackHistory = 1 << 7, // Callback on pressing Up/Down arrows (for history handling)
	ImGuiInputTextFlags_CallbackAlways = 1 << 8, // Callback on each iteration. User code may query cursor position, modify text buffer.
	ImGuiInputTextFlags_CallbackCharFilter = 1 << 9, // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
	ImGuiInputTextFlags_AllowTabInput = 1 << 10, // Pressing TAB input a '\t' character into the text field
	ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11, // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
	ImGuiInputTextFlags_NoHorizontalScroll = 1 << 12, // Disable following the cursor horizontally
	ImGuiInputTextFlags_AlwaysInsertMode = 1 << 13, // Insert mode
	ImGuiInputTextFlags_ReadOnly = 1 << 14, // Read-only mode
	ImGuiInputTextFlags_Password = 1 << 15, // Password mode, display all characters as '*'
	ImGuiInputTextFlags_NoUndoRedo = 1 << 16, // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
	ImGuiInputTextFlags_CharsScientific = 1 << 17, // Allow 0123456789.+-*/eE (Scientific notation input)
	ImGuiInputTextFlags_CallbackResize = 1 << 18, // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
	// [Internal]
	ImGuiInputTextFlags_Multiline = 1 << 20, // For internal use by InputTextMultiline()
	ImGuiInputTextFlags_NoMarkEdited = 1 << 21 // For internal use by functions using InputText() before reformatting data
};

enum ImGuiTreeNodeFlags_
{
	ImGuiTreeNodeFlags_None = 0,
	ImGuiTreeNodeFlags_Selected = 1 << 0, // Draw as selected
	ImGuiTreeNodeFlags_Framed = 1 << 1, // Full colored frame (e.g. for CollapsingHeader)
	ImGuiTreeNodeFlags_AllowItemOverlap = 1 << 2, // Hit testing to allow subsequent widgets to overlap this one
	ImGuiTreeNodeFlags_NoTreePushOnOpen = 1 << 3, // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
	ImGuiTreeNodeFlags_NoAutoOpenOnLog = 1 << 4, // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
	ImGuiTreeNodeFlags_DefaultOpen = 1 << 5, // Default node to be open
	ImGuiTreeNodeFlags_OpenOnDoubleClick = 1 << 6, // Need double-click to open node
	ImGuiTreeNodeFlags_OpenOnArrow = 1 << 7, // Only open when clicking on the arrow part. If ImGuiTreeNodeFlags_OpenOnDoubleClick is also set, single-click arrow or double-click all box to open.
	ImGuiTreeNodeFlags_Leaf = 1 << 8, // No collapsing, no arrow (use as a convenience for leaf nodes).
	ImGuiTreeNodeFlags_Bullet = 1 << 9, // Display a bullet instead of arrow
	ImGuiTreeNodeFlags_FramePadding = 1 << 10, // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding().
	ImGuiTreeNodeFlags_SpanAvailWidth = 1 << 11, // Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line. In the future we may refactor the hit system to be front-to-back, allowing natural overlaps and then this can become the default.
	ImGuiTreeNodeFlags_SpanFullWidth = 1 << 12, // Extend hit box to the left-most and right-most edges (bypass the indented area).
	ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 13, // (WIP) Nav: left direction may move to this TreeNode() from any of its child (items submitted between TreeNode and TreePop)
	//ImGuiTreeNodeFlags_NoScrollOnOpen = 1 << 14, // FIXME: TODO: Disable automatic scroll on TreePop() if node got just open and contents is not visible
	ImGuiTreeNodeFlags_CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog
};

enum ImGuiSelectableFlags_
{
	ImGuiSelectableFlags_None = 0,
	ImGuiSelectableFlags_DontClosePopups = 1 << 0, // Clicking this don't close parent popup window
	ImGuiSelectableFlags_SpanAllColumns = 1 << 1, // Selectable frame can span all columns (text will still fit in current column)
	ImGuiSelectableFlags_AllowDoubleClick = 1 << 2, // Generate press events on double clicks too
	ImGuiSelectableFlags_Disabled = 1 << 3, // Cannot be selected, display grayed out text
	ImGuiSelectableFlags_AllowItemOverlap = 1 << 4 // (WIP) Hit testing to allow subsequent widgets to overlap this one
};

enum ImGuiComboFlags_
{
	ImGuiComboFlags_None = 0,
	ImGuiComboFlags_PopupAlignLeft = 1 << 0, // Align the popup toward the left by default
	ImGuiComboFlags_HeightSmall = 1 << 1, // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
	ImGuiComboFlags_HeightRegular = 1 << 2, // Max ~8 items visible (default)
	ImGuiComboFlags_HeightLarge = 1 << 3, // Max ~20 items visible
	ImGuiComboFlags_HeightLargest = 1 << 4, // As many fitting items as possible
	ImGuiComboFlags_NoArrowButton = 1 << 5, // Display on the preview box without the square arrow button
	ImGuiComboFlags_NoPreview = 1 << 6, // Display only a square arrow button
	ImGuiComboFlags_HeightMask_ = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest
};

enum ImGuiTabBarFlags_
{
	ImGuiTabBarFlags_None = 0,
	ImGuiTabBarFlags_Reorderable = 1 << 0, // Allow manually dragging tabs to re-order them + New tabs are appended at the end of list
	ImGuiTabBarFlags_AutoSelectNewTabs = 1 << 1, // Automatically select new tabs when they appear
	ImGuiTabBarFlags_TabListPopupButton = 1 << 2, // Disable buttons to open the tab list popup
	ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 1 << 3, // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You can still repro this behavior on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
	ImGuiTabBarFlags_NoTabListScrollingButtons = 1 << 4, // Disable scrolling buttons (apply when fitting policy is ImGuiTabBarFlags_FittingPolicyScroll)
	ImGuiTabBarFlags_NoTooltip = 1 << 5, // Disable tooltips when hovering a tab
	ImGuiTabBarFlags_FittingPolicyResizeDown = 1 << 6, // Resize tabs when they don't fit
	ImGuiTabBarFlags_FittingPolicyScroll = 1 << 7, // Add scroll buttons when tabs don't fit
	ImGuiTabBarFlags_FittingPolicyMask_ = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll,
	ImGuiTabBarFlags_FittingPolicyDefault_ = ImGuiTabBarFlags_FittingPolicyResizeDown
};

enum ImGuiTabItemFlags_
{
	ImGuiTabItemFlags_None = 0,
	ImGuiTabItemFlags_UnsavedDocument = 1 << 0, // Append '*' to title without affecting the ID, as a convenience to avoid using the ### operator. Also: tab is selected on closure and closure is deferred by one frame to allow code to undo it without flicker.
	ImGuiTabItemFlags_SetSelected = 1 << 1, // Trigger flag to programmatically make the tab selected when calling BeginTabItem()
	ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 1 << 2, // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You can still repro this behavior on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
	ImGuiTabItemFlags_NoPushId = 1 << 3 // Don't call PushID(tab->ID)/PopID() on BeginTabItem()/EndTabItem()
};

enum ImGuiFocusedFlags_
{
	ImGuiFocusedFlags_None = 0,
	ImGuiFocusedFlags_ChildWindows = 1 << 0, // IsWindowFocused(): Return true if any children of the window is focused
	ImGuiFocusedFlags_RootWindow = 1 << 1, // IsWindowFocused(): Test from root window (top most parent of the current hierarchy)
	ImGuiFocusedFlags_AnyWindow = 1 << 2, // IsWindowFocused(): Return true if any window is focused. Important: If you are trying to tell how to dispatch your low-level inputs, do NOT use this. Use 'io.WantCaptureMouse' instead! Please read the FAQ!
	ImGuiFocusedFlags_RootAndChildWindows = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows
};

enum ImGuiHoveredFlags_
{
	ImGuiHoveredFlags_None = 0, // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
	ImGuiHoveredFlags_ChildWindows = 1 << 0, // IsWindowHovered() only: Return true if any children of the window is hovered
	ImGuiHoveredFlags_RootWindow = 1 << 1, // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
	ImGuiHoveredFlags_AnyWindow = 1 << 2, // IsWindowHovered() only: Return true if any window is hovered
	ImGuiHoveredFlags_AllowWhenBlockedByPopup = 1 << 3, // Return true even if a popup window is normally blocking access to this item/window
	//ImGuiHoveredFlags_AllowWhenBlockedByModal = 1 << 4, // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Unavailable yet.
	ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 5, // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
	ImGuiHoveredFlags_AllowWhenOverlapped = 1 << 6, // Return true even if the position is obstructed or overlapped by another window
	ImGuiHoveredFlags_AllowWhenDisabled = 1 << 7, // Return true even if the item is disabled
	ImGuiHoveredFlags_RectOnly = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
	ImGuiHoveredFlags_RootAndChildWindows = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows
};

enum ImGuiDragDropFlags_
{
	ImGuiDragDropFlags_None = 0,
	ImGuiDragDropFlags_SourceNoPreviewTooltip = 1 << 0, // By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disable this behavior.
	ImGuiDragDropFlags_SourceNoDisableHover = 1 << 1, // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disable this behavior so you can still call IsItemHovered() on the source item.
	ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2, // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
	ImGuiDragDropFlags_SourceAllowNullID = 1 << 3, // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear imgui ecosystem and so we made it explicit.
	ImGuiDragDropFlags_SourceExtern = 1 << 4, // External source (from outside of dear imgui), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
	ImGuiDragDropFlags_SourceAutoExpirePayload = 1 << 5, // Automatically expire the payload if the source cease to be submitted (otherwise payloads are persisting while being dragged)
	ImGuiDragDropFlags_AcceptBeforeDelivery = 1 << 10, // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
	ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11, // Do not draw the default highlight rectangle when hovering over target.
	ImGuiDragDropFlags_AcceptNoPreviewTooltip = 1 << 12, // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
	ImGuiDragDropFlags_AcceptPeekOnly = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect // For peeking ahead and inspecting the payload before delivery.
};

enum ImGuiDataType_
{
	ImGuiDataType_S8, // signed char / char (with sensible compilers)
	ImGuiDataType_U8, // unsigned char
	ImGuiDataType_S16, // short
	ImGuiDataType_U16, // unsigned short
	ImGuiDataType_S32, // int
	ImGuiDataType_U32, // unsigned int
	ImGuiDataType_S64, // long long / __int64
	ImGuiDataType_U64, // unsigned long long / unsigned __int64
	ImGuiDataType_Float, // float
	ImGuiDataType_Double, // double
	ImGuiDataType_COUNT
};

enum
{
	ImGuiDataType_Int,
	ImGuiDataType_Float1,
	ImGuiDataType_Float2
};

enum ImGuiDir_
{
	ImGuiDir_None = -1,
	ImGuiDir_Left = 0,
	ImGuiDir_Right = 1,
	ImGuiDir_Up = 2,
	ImGuiDir_Down = 3,
	ImGuiDir_COUNT
};

enum ImGuiKey_
{
	ImGuiKey_Tab,
	ImGuiKey_LeftArrow,
	ImGuiKey_RightArrow,
	ImGuiKey_UpArrow,
	ImGuiKey_DownArrow,
	ImGuiKey_PageUp,
	ImGuiKey_PageDown,
	ImGuiKey_Home,
	ImGuiKey_End,
	ImGuiKey_Insert,
	ImGuiKey_Delete,
	ImGuiKey_Backspace,
	ImGuiKey_Space,
	ImGuiKey_Enter,
	ImGuiKey_Escape,
	ImGuiKey_KeyPadEnter,
	ImGuiKey_A, // for text edit CTRL+A: select all
	ImGuiKey_C, // for text edit CTRL+C: copy
	ImGuiKey_V, // for text edit CTRL+V: paste
	ImGuiKey_X, // for text edit CTRL+X: cut
	ImGuiKey_Y, // for text edit CTRL+Y: redo
	ImGuiKey_Z, // for text edit CTRL+Z: undo
	ImGuiKey_COUNT
};

enum ImGuiKeyModFlags_
{
	ImGuiKeyModFlags_None = 0,
	ImGuiKeyModFlags_Ctrl = 1 << 0,
	ImGuiKeyModFlags_Shift = 1 << 1,
	ImGuiKeyModFlags_Alt = 1 << 2,
	ImGuiKeyModFlags_Super = 1 << 3
};

enum ImGuiNavInput_
{
	// Gamepad Mapping
	ImGuiNavInput_Activate, // activate / open / toggle / tweak value // e.g. Cross (PS4), A (Xbox), A (Switch), Space (Keyboard)
	ImGuiNavInput_Cancel, // cancel / close / exit // e.g. Circle (PS4), B (Xbox), B (Switch), Escape (Keyboard)
	ImGuiNavInput_Input, // text input / on-screen keyboard // e.g. Triang.(PS4), Y (Xbox), X (Switch), Return (Keyboard)
	ImGuiNavInput_Menu, // tap: toggle menu / hold: focus, move, resize // e.g. Square (PS4), X (Xbox), Y (Switch), Alt (Keyboard)
	ImGuiNavInput_DpadLeft, // move / tweak / resize window (w/ PadMenu) // e.g. D-pad Left/Right/Up/Down (Gamepads), Arrow keys (Keyboard)
	ImGuiNavInput_DpadRight, //
	ImGuiNavInput_DpadUp, //
	ImGuiNavInput_DpadDown, //
	ImGuiNavInput_LStickLeft, // scroll / move window (w/ PadMenu) // e.g. Left Analog Stick Left/Right/Up/Down
	ImGuiNavInput_LStickRight, //
	ImGuiNavInput_LStickUp, //
	ImGuiNavInput_LStickDown, //
	ImGuiNavInput_FocusPrev, // next window (w/ PadMenu) // e.g. L1 or L2 (PS4), LB or LT (Xbox), L or ZL (Switch)
	ImGuiNavInput_FocusNext, // prev window (w/ PadMenu) // e.g. R1 or R2 (PS4), RB or RT (Xbox), R or ZL (Switch)
	ImGuiNavInput_TweakSlow, // slower tweaks // e.g. L1 or L2 (PS4), LB or LT (Xbox), L or ZL (Switch)
	ImGuiNavInput_TweakFast, // faster tweaks // e.g. R1 or R2 (PS4), RB or RT (Xbox), R or ZL (Switch)

	// [Internal] Don't use directly! This is used internally to differentiate keyboard from gamepad inputs for behaviors that require to differentiate them.
	// Keyboard behavior that have no corresponding gamepad mapping (e.g. CTRL+TAB) will be directly reading from io.KeysDown[] instead of io.NavInputs[].
	ImGuiNavInput_KeyMenu_, // toggle menu // = io.KeyAlt
	ImGuiNavInput_KeyLeft_, // move left // = Arrow keys
	ImGuiNavInput_KeyRight_, // move right
	ImGuiNavInput_KeyUp_, // move up
	ImGuiNavInput_KeyDown_, // move down
	ImGuiNavInput_COUNT,
	ImGuiNavInput_InternalStart_ = ImGuiNavInput_KeyMenu_
};

enum ImGuiConfigFlags_
{
	ImGuiConfigFlags_None = 0,
	ImGuiConfigFlags_NavEnableKeyboard = 1 << 0, // Master keyboard navigation enable flag. NewFrame() will automatically fill io.NavInputs[] based on io.KeysDown[].
	ImGuiConfigFlags_NavEnableGamepad = 1 << 1, // Master gamepad navigation enable flag. This is mostly to instruct your imgui back-end to fill io.NavInputs[]. Back-end also needs to set ImGuiBackendFlags_HasGamepad.
	ImGuiConfigFlags_NavEnableSetMousePos = 1 << 2, // Instruct navigation to move the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is awkward. Will update io.MousePos and set io.WantSetMousePos=true. If enabled you MUST honor io.WantSetMousePos requests in your binding, otherwise ImGui will react as if the mouse is jumping around back and forth.
	ImGuiConfigFlags_NavNoCaptureKeyboard = 1 << 3, // Instruct navigation to not set the io.WantCaptureKeyboard flag when io.NavActive is set.
	ImGuiConfigFlags_NoMouse = 1 << 4, // Instruct imgui to clear mouse position/buttons in NewFrame(). This allows ignoring the mouse information set by the back-end.
	ImGuiConfigFlags_NoMouseCursorChange = 1 << 5, // Instruct back-end to not alter mouse cursor shape and visibility. Use if the back-end cursor changes are interfering with yours and you don't want to use SetMouseCursor() to change mouse cursor. You may want to honor requests from imgui by reading GetMouseCursor() yourself instead.

	// User storage (to allow your back-end/engine to communicate to code that may be shared between multiple projects. Those flags are not used by core Dear ImGui)
	ImGuiConfigFlags_IsSRGB = 1 << 20, // Application is SRGB-aware.
	ImGuiConfigFlags_IsTouchScreen = 1 << 21 // Application is using a touch screen instead of a mouse.
};

enum ImGuiBackendFlags_
{
	ImGuiBackendFlags_None = 0,
	ImGuiBackendFlags_HasGamepad = 1 << 0, // Back-end Platform supports gamepad and currently has one connected.
	ImGuiBackendFlags_HasMouseCursors = 1 << 1, // Back-end Platform supports honoring GetMouseCursor() value to change the OS cursor shape.
	ImGuiBackendFlags_HasSetMousePos = 1 << 2, // Back-end Platform supports io.WantSetMousePos requests to reposition the OS mouse position (only used if ImGuiConfigFlags_NavEnableSetMousePos is set).
	ImGuiBackendFlags_RendererHasVtxOffset = 1 << 3 // Back-end Renderer supports ImDrawCmd::VtxOffset. This enables output of large meshes (64K+ vertices) while still using 16-bit indices.
};

enum ImGuiCol_
{
	ImGuiCol_Text,
	ImGuiCol_TextDisabled,
	ImGuiCol_WindowBg, // Background of normal windows
	ImGuiCol_ChildBg, // Background of child windows
	ImGuiCol_PopupBg, // Background of popups, menus, tooltips windows
	ImGuiCol_Border,
	ImGuiCol_BorderShadow,
	ImGuiCol_FrameBg, // Background of checkbox, radio button, plot, slider, text input
	ImGuiCol_FrameBgHovered,
	ImGuiCol_FrameBgActive,
	ImGuiCol_TitleBg,
	ImGuiCol_TitleBgActive,
	ImGuiCol_TitleBgCollapsed,
	ImGuiCol_MenuBarBg,
	ImGuiCol_ScrollbarBg,
	ImGuiCol_ScrollbarGrab,
	ImGuiCol_ScrollbarGrabHovered,
	ImGuiCol_ScrollbarGrabActive,
	ImGuiCol_CheckMark,
	ImGuiCol_SliderGrab,
	ImGuiCol_SliderGrabActive,
	ImGuiCol_Button,
	ImGuiCol_ButtonHovered,
	ImGuiCol_ButtonActive,
	ImGuiCol_Header, // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
	ImGuiCol_HeaderHovered,
	ImGuiCol_HeaderActive,
	ImGuiCol_Separator,
	ImGuiCol_SeparatorHovered,
	ImGuiCol_SeparatorActive,
	ImGuiCol_ResizeGrip,
	ImGuiCol_ResizeGripHovered,
	ImGuiCol_ResizeGripActive,
	ImGuiCol_Tab,
	ImGuiCol_TabHovered,
	ImGuiCol_TabActive,
	ImGuiCol_TabUnfocused,
	ImGuiCol_TabUnfocusedActive,
	ImGuiCol_PlotLines,
	ImGuiCol_PlotLinesHovered,
	ImGuiCol_PlotHistogram,
	ImGuiCol_PlotHistogramHovered,
	ImGuiCol_TextSelectedBg,
	ImGuiCol_DragDropTarget,
	ImGuiCol_NavHighlight, // Gamepad/keyboard: current highlighted item
	ImGuiCol_NavWindowingHighlight, // Highlight window when using CTRL+TAB
	ImGuiCol_NavWindowingDimBg, // Darken/colorize entire screen behind the CTRL+TAB window list, when active
	ImGuiCol_ModalWindowDimBg, // Darken/colorize entire screen behind a modal window, when one is active
	ImGuiCol_COUNT

	// Obsolete names (will be removed)
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
	, ImGuiCol_ModalWindowDarkening = ImGuiCol_ModalWindowDimBg // [renamed in 1.63]
	//, ImGuiCol_CloseButton, ImGuiCol_CloseButtonActive, ImGuiCol_CloseButtonHovered// [unused since 1.60+] the close button now uses regular button colors.
#endif
};

enum ImGuiStyleVar_
{
	// Enum name --------------------- // Member in ImGuiStyle structure (see ImGuiStyle for descriptions)
	ImGuiStyleVar_Alpha, // float Alpha
	ImGuiStyleVar_WindowPadding, // ImVec2 WindowPadding
	ImGuiStyleVar_WindowRounding, // float WindowRounding
	ImGuiStyleVar_WindowBorderSize, // float WindowBorderSize
	ImGuiStyleVar_WindowMinSize, // ImVec2 WindowMinSize
	ImGuiStyleVar_WindowTitleAlign, // ImVec2 WindowTitleAlign
	ImGuiStyleVar_ChildRounding, // float ChildRounding
	ImGuiStyleVar_ChildBorderSize, // float ChildBorderSize
	ImGuiStyleVar_PopupRounding, // float PopupRounding
	ImGuiStyleVar_PopupBorderSize, // float PopupBorderSize
	ImGuiStyleVar_FramePadding, // ImVec2 FramePadding
	ImGuiStyleVar_FrameRounding, // float FrameRounding
	ImGuiStyleVar_FrameBorderSize, // float FrameBorderSize
	ImGuiStyleVar_ItemSpacing, // ImVec2 ItemSpacing
	ImGuiStyleVar_ItemInnerSpacing, // ImVec2 ItemInnerSpacing
	ImGuiStyleVar_IndentSpacing, // float IndentSpacing
	ImGuiStyleVar_ScrollbarSize, // float ScrollbarSize
	ImGuiStyleVar_ScrollbarRounding, // float ScrollbarRounding
	ImGuiStyleVar_GrabMinSize, // float GrabMinSize
	ImGuiStyleVar_GrabRounding, // float GrabRounding
	ImGuiStyleVar_TabRounding, // float TabRounding
	ImGuiStyleVar_ButtonTextAlign, // ImVec2 ButtonTextAlign
	ImGuiStyleVar_SelectableTextAlign, // ImVec2 SelectableTextAlign
	ImGuiStyleVar_COUNT

	// Obsolete names (will be removed)
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
	, ImGuiStyleVar_Count_ = ImGuiStyleVar_COUNT // [renamed in 1.60]
#endif
};

enum ImGuiColorEditFlags_
{
	ImGuiColorEditFlags_None = 0,
	ImGuiColorEditFlags_NoAlpha = 1 << 1, // // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (will only read 3 components from the input pointer).
	ImGuiColorEditFlags_NoPicker = 1 << 2, // // ColorEdit: disable picker when clicking on colored square.
	ImGuiColorEditFlags_NoOptions = 1 << 3, // // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
	ImGuiColorEditFlags_NoSmallPreview = 1 << 4, // // ColorEdit, ColorPicker: disable colored square preview next to the inputs. (e.g. to show only the inputs)
	ImGuiColorEditFlags_NoInputs = 1 << 5, // // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview colored square).
	ImGuiColorEditFlags_NoTooltip = 1 << 6, // // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
	ImGuiColorEditFlags_NoLabel = 1 << 7, // // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
	ImGuiColorEditFlags_NoSidePreview = 1 << 8, // // ColorPicker: disable bigger color preview on right side of the picker, use small colored square preview instead.
	ImGuiColorEditFlags_NoDragDrop = 1 << 9, // // ColorEdit: disable drag and drop target. ColorButton: disable drag and drop source.
	ImGuiColorEditFlags_NoBorder = 1 << 10, // // ColorButton: disable border (which is enforced by default)

	// User Options (right-click on widget to change some of them).
	ImGuiColorEditFlags_AlphaBar = 1 << 16, // // ColorEdit, ColorPicker: show vertical alpha bar/gradient in picker.
	ImGuiColorEditFlags_AlphaPreview = 1 << 17, // // ColorEdit, ColorPicker, ColorButton: display preview as a transparent color over a checkerboard, instead of opaque.
	ImGuiColorEditFlags_AlphaPreviewHalf = 1 << 18, // // ColorEdit, ColorPicker, ColorButton: display half opaque / half checkerboard, instead of opaque.
	ImGuiColorEditFlags_HDR = 1 << 19, // // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use ImGuiColorEditFlags_Float flag as well).
	ImGuiColorEditFlags_DisplayRGB = 1 << 20, // [Display] // ColorEdit: override _display_ type among RGB/HSV/Hex. ColorPicker: select any combination using one or more of RGB/HSV/Hex.
	ImGuiColorEditFlags_DisplayHSV = 1 << 21, // [Display] // "
	ImGuiColorEditFlags_DisplayHex = 1 << 22, // [Display] // "
	ImGuiColorEditFlags_Uint8 = 1 << 23, // [DataType] // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255.
	ImGuiColorEditFlags_Float = 1 << 24, // [DataType] // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.
	ImGuiColorEditFlags_PickerHueBar = 1 << 25, // [Picker] // ColorPicker: bar for Hue, rectangle for Sat/Value.
	ImGuiColorEditFlags_PickerHueWheel = 1 << 26, // [Picker] // ColorPicker: wheel for Hue, triangle for Sat/Value.
	ImGuiColorEditFlags_InputRGB = 1 << 27, // [Input] // ColorEdit, ColorPicker: input and output data in RGB format.
	ImGuiColorEditFlags_InputHSV = 1 << 28, // [Input] // ColorEdit, ColorPicker: input and output data in HSV format.

	// Defaults Options. You can set application defaults using SetColorEditOptions(). The intent is that you probably don't want to
	// override them in most of your calls. Let the user choose via the option menu and/or call SetColorEditOptions() once during startup.
	ImGuiColorEditFlags__OptionsDefault = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,

	// [Internal] Masks
	ImGuiColorEditFlags__DisplayMask = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex,
	ImGuiColorEditFlags__DataTypeMask = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float,
	ImGuiColorEditFlags__PickerMask = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar,
	ImGuiColorEditFlags__InputMask = ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_InputHSV

	// Obsolete names (will be removed)
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
	, ImGuiColorEditFlags_RGB = ImGuiColorEditFlags_DisplayRGB, ImGuiColorEditFlags_HSV = ImGuiColorEditFlags_DisplayHSV, ImGuiColorEditFlags_HEX = ImGuiColorEditFlags_DisplayHex // [renamed in 1.69]
#endif
};

enum ImGuiMouseButton_
{
	ImGuiMouseButton_Left = 0,
	ImGuiMouseButton_Right = 1,
	ImGuiMouseButton_Middle = 2,
	ImGuiMouseButton_COUNT = 5
};

enum ImGuiMouseCursor_
{
	ImGuiMouseCursor_None = -1,
	ImGuiMouseCursor_Arrow = 0,
	ImGuiMouseCursor_TextInput, // When hovering over InputText, etc.
	ImGuiMouseCursor_ResizeAll, // (Unused by Dear ImGui functions)
	ImGuiMouseCursor_ResizeNS, // When hovering over an horizontal border
	ImGuiMouseCursor_ResizeEW, // When hovering over a vertical border or a column
	ImGuiMouseCursor_ResizeNESW, // When hovering over the bottom-left corner of a window
	ImGuiMouseCursor_ResizeNWSE, // When hovering over the bottom-right corner of a window
	ImGuiMouseCursor_Hand, // (Unused by Dear ImGui functions. Use for e.g. hyperlinks)
	ImGuiMouseCursor_NotAllowed, // When hovering something with disallowed interaction. Usually a crossed circle.
	ImGuiMouseCursor_COUNT

	// Obsolete names (will be removed)
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
	, ImGuiMouseCursor_Count_ = ImGuiMouseCursor_COUNT // [renamed in 1.60]
#endif
};

enum ImGuiCond_
{
	ImGuiCond_Always = 1 << 0, // Set the variable
	ImGuiCond_Once = 1 << 1, // Set the variable once per runtime session (only the first call with succeed)
	ImGuiCond_FirstUseEver = 1 << 2, // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
	ImGuiCond_Appearing = 1 << 3 // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
};

struct ImNewDummy {};

inline void* operator new(size_t, ImNewDummy, void* ptr) { return ptr; }

inline void operator delete(void*, ImNewDummy, void*) {}

#define IM_PLACEMENT_NEW(_PTR) new(ImNewDummy(), _PTR)

#define IM_NEW(_TYPE) new(ImNewDummy(), ImGui::MemAlloc(sizeof(_TYPE))) _TYPE

template<typename T> void IM_DELETE(T* p) { if (p) { p->~T(); ImGui::MemFree(p); } }

template<typename T>

struct ImVector
{
	int Size;
	int Capacity;
	T* Data;

	// Provide standard typedefs but we don't use them ourselves.
	typedef T value_type;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;

	// Constructors, destructor
	inline ImVector() { Size = Capacity = 0; Data = NULL; }
	inline ImVector(const ImVector<T>& src) { Size = Capacity = 0; Data = NULL; operator=(src); }
	inline ImVector<T>& operator=(const ImVector<T>& src) { clear(); resize(src.Size); memcpy(Data, src.Data, (size_t)Size * sizeof(T)); return *this; }
	inline ~ImVector() { if (Data) ImGui::MemFree(Data); }

	inline bool empty() const { return Size == 0; }
	inline int size() const { return Size; }
	inline int size_in_bytes() const { return Size * (int)sizeof(T); }
	inline int capacity() const { return Capacity; }
	inline T& operator[](int i) { return Data[i]; }
	inline const T& operator[](int i) const { return Data[i]; }

	inline void clear() { if (Data) { Size = Capacity = 0; ImGui::MemFree(Data); Data = NULL; } }
	inline T* begin() { return Data; }
	inline const T* begin() const { return Data; }
	inline T* end() { return Data + Size; }
	inline const T* end() const { return Data + Size; }
	inline T& front() { return Data[0]; }
	inline const T& front() const { return Data[0]; }
	inline T& back() { return Data[Size - 1]; }
	inline const T& back() const { return Data[Size - 1]; }
	inline void swap(ImVector<T>& rhs) { int rhs_size = rhs.Size; rhs.Size = Size; Size = rhs_size; int rhs_cap = rhs.Capacity; rhs.Capacity = Capacity; Capacity = rhs_cap; T* rhs_data = rhs.Data; rhs.Data = Data; Data = rhs_data; }

	inline int _grow_capacity(int sz) const { int new_capacity = Capacity ? (Capacity + Capacity / 2) : 8; return new_capacity > sz ? new_capacity : sz; }
	inline void resize(int new_size) { if (new_size > Capacity) reserve(_grow_capacity(new_size)); Size = new_size; }
	inline void resize(int new_size, const T& v) { if (new_size > Capacity) reserve(_grow_capacity(new_size)); if (new_size > Size) for (int n = Size; n < new_size; n++) memcpy(&Data[n], &v, sizeof(v)); Size = new_size; }
	inline void shrink(int new_size) { Size = new_size; } // Resize a vector to a smaller size, guaranteed not to cause a reallocation
	inline void reserve(int new_capacity) { if (new_capacity <= Capacity) return; T* new_data = (T*)ImGui::MemAlloc((size_t)new_capacity * sizeof(T)); if (Data) { memcpy(new_data, Data, (size_t)Size * sizeof(T)); ImGui::MemFree(Data); } Data = new_data; Capacity = new_capacity; }

	// NB: It is illegal to call push_back/push_front/insert with a reference pointing inside the ImVector data itself! e.g. v.push_back(v[10]) is forbidden.
	inline void push_back(const T& v) { if (Size == Capacity) reserve(_grow_capacity(Size + 1)); memcpy(&Data[Size], &v, sizeof(v)); Size++; }
	inline void pop_back() { Size--; }
	inline void push_front(const T& v) { if (Size == 0) push_back(v); else insert(Data, v); }
	inline T* erase(const T* it) { const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + 1, ((size_t)Size - (size_t)off - 1) * sizeof(T)); Size--; return Data + off; }
	inline T* erase(const T* it, const T* it_last) { const ptrdiff_t count = it_last - it; const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + count, ((size_t)Size - (size_t)off - count) * sizeof(T)); Size -= (int)count; return Data + off; }
	inline T* erase_unsorted(const T* it) { const ptrdiff_t off = it - Data; if (it < Data + Size - 1) memcpy(Data + off, Data + Size - 1, sizeof(T)); Size--; return Data + off; }
	inline T* insert(const T* it, const T& v) { const ptrdiff_t off = it - Data; if (Size == Capacity) reserve(_grow_capacity(Size + 1)); if (off < (int)Size) memmove(Data + off + 1, Data + off, ((size_t)Size - (size_t)off) * sizeof(T)); memcpy(&Data[off], &v, sizeof(v)); Size++; return Data + off; }
	inline bool contains(const T& v) const { const T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data++ == v) return true; return false; }
	inline T* find(const T& v) { T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data == v) break; else ++data; return data; }
	inline const T* find(const T& v) const { const T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data == v) break; else ++data; return data; }
	inline bool find_erase(const T& v) { const T* it = find(v); if (it < Data + Size) { erase(it); return true; } return false; }
	inline bool find_erase_unsorted(const T& v) { const T* it = find(v); if (it < Data + Size) { erase_unsorted(it); return true; } return false; }
	inline int index_from_ptr(const T* it) const { const ptrdiff_t off = it - Data; return (int)off; }
};

struct ImGuiStyle
{
	float Alpha; // Global alpha applies to everything in Dear ImGui.
	ImVec2 WindowPadding; // Padding within a window.
	float WindowRounding; // Radius of window corners rounding. Set to 0.0f to have rectangular windows.
	float WindowBorderSize; // Thickness of border around windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
	ImVec2 WindowMinSize; // Minimum window size. This is a global setting. If you want to constraint individual windows, use SetNextWindowSizeConstraints().
	ImVec2 WindowTitleAlign; // Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
	ImGuiDir WindowMenuButtonPosition; // Side of the collapsing/docking button in the title bar (None/Left/Right). Defaults to ImGuiDir_Left.
	float ChildRounding; // Radius of child window corners rounding. Set to 0.0f to have rectangular windows.
	float ChildBorderSize; // Thickness of border around child windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
	float PopupRounding; // Radius of popup window corners rounding. (Note that tooltip windows use WindowRounding)
	float PopupBorderSize; // Thickness of border around popup/tooltip windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
	ImVec2 FramePadding; // Padding within a framed rectangle (used by most widgets).
	float FrameRounding; // Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
	float FrameBorderSize; // Thickness of border around frames. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
	ImVec2 ItemSpacing; // Horizontal and vertical spacing between widgets/lines.
	ImVec2 ItemInnerSpacing; // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label).
	ImVec2 TouchExtraPadding; // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	float IndentSpacing; // Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	float ColumnsMinSpacing; // Minimum horizontal spacing between two columns. Preferably > (FramePadding.x + 1).
	float ScrollbarSize; // Width of the vertical scrollbar, Height of the horizontal scrollbar.
	float ScrollbarRounding; // Radius of grab corners for scrollbar.
	float GrabMinSize; // Minimum width/height of a grab box for slider/scrollbar.
	float GrabRounding; // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	float TabRounding; // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
	float TabBorderSize; // Thickness of border around tabs.
	ImGuiDir ColorButtonPosition; // Side of the color button in the ColorEdit4 widget (left/right). Defaults to ImGuiDir_Right.
	ImVec2 ButtonTextAlign; // Alignment of button text when button is larger than text. Defaults to (0.5f, 0.5f) (centered).
	ImVec2 SelectableTextAlign; // Alignment of selectable text. Defaults to (0.0f, 0.0f) (top-left aligned). It's generally important to keep this left-aligned if you want to lay multiple items on a same line.
	ImVec2 DisplayWindowPadding; // Window position are clamped to be visible within the display area by at least this amount. Only applies to regular windows.
	ImVec2 DisplaySafeAreaPadding; // If you cannot see the edges of your screen (e.g. on a TV) increase the safe area padding. Apply to popups/tooltips as well regular windows. NB: Prefer configuring your TV sets correctly!
	float MouseCursorScale; // Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). May be removed later.
	bool AntiAliasedLines; // Enable anti-aliasing on lines/borders. Disable if you are really tight on CPU/GPU.
	bool AntiAliasedFill; // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
	float CurveTessellationTol; // Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
	float CircleSegmentMaxError; // Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled() or drawing rounded corner rectangles with no explicit segment count specified. Decrease for higher quality but more geometry.
	ImVec4 Colors[ImGuiCol_COUNT];

	ImGuiStyle();
	void ScaleAllSizes(float scale_factor);
};

struct ImGuiIO
{
	ImGuiConfigFlags ConfigFlags;
	ImGuiBackendFlags BackendFlags;
	ImVec2 DisplaySize;
	float DeltaTime;
	float MouseDoubleClickTime;
	float MouseDoubleClickMaxDist;
	float MouseDragThreshold;
	int KeyMap[ImGuiKey_COUNT]; // <unset> // Map of indices into the KeysDown[512] entries array which represent your "native" keyboard state.
	float KeyRepeatDelay; // = 0.250f // When holding a key/button, time before it starts repeating, in seconds (for buttons in Repeat mode, etc.).
	float KeyRepeatRate; // = 0.050f // When holding a key/button, rate at which it repeats, in seconds.
	void* UserData; // = NULL // Store your own data for retrieval by callbacks.

	ImFontAtlas*Fonts; // <auto> // Font atlas: load, rasterize and pack one or more fonts into a single texture.
	float FontGlobalScale; // = 1.0f // Global scale all fonts
	bool FontAllowUserScaling; // = false // Allow user scaling text of individual window with CTRL+Wheel.
	ImFont* FontDefault; // = NULL // Font to use on NewFrame(). Use NULL to uses Fonts->Fonts[0].
	ImVec2 DisplayFramebufferScale; // = (1, 1) // For retina display or other situations where window coordinates are different from framebuffer coordinates. This generally ends up in ImDrawData::FramebufferScale.

	// Miscellaneous options
	bool MouseDrawCursor; // = false // Request ImGui to draw a mouse cursor for you (if you are on a platform without a mouse cursor). Cannot be easily renamed to 'io.ConfigXXX' because this is frequently used by back-end implementations.
	bool ConfigMacOSXBehaviors;
	bool ConfigInputTextCursorBlink; // = true // Set to false to disable blinking cursor, for users who consider it distracting. (was called: io.OptCursorBlink prior to 1.63)
	bool ConfigWindowsResizeFromEdges; // = true // Enable resizing of windows from their edges and from the lower-left corner. This requires (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors) because it needs mouse cursor feedback. (This used to be a per-window ImGuiWindowFlags_ResizeFromAnySide flag)
	bool ConfigWindowsMoveFromTitleBarOnly; // = false // [BETA] Set to true to only allow moving windows when clicked+dragged from the title bar. Windows without a title bar are not affected.
	float ConfigWindowsMemoryCompactTimer;// = 60.0f // [BETA] Compact window memory usage when unused. Set to -1.0f to disable.

	//------------------------------------------------------------------
	// Platform Functions
	// (the imgui_impl_xxxx back-end files are setting those up for you)
	//------------------------------------------------------------------

	// Optional: Platform/Renderer back-end name (informational only! will be displayed in About Window) + User data for back-end/wrappers to store their own stuff.
	void* BackendPlatformUserData; // = NULL // User data for platform back-end
	void* BackendRendererUserData; // = NULL // User data for renderer back-end
	void* BackendLanguageUserData; // = NULL // User data for non C++ programming language back-end

	// Optional: Access OS clipboard
	// (default to use native Win32 clipboard on Windows, otherwise uses a private clipboard. Override to access OS clipboard on other architectures)
	const char* (*GetClipboardTextFn)(void* user_data);
	void(*SetClipboardTextFn)(void* user_data, const char* text);
	void* ClipboardUserData;

	// Optional: Notify OS Input Method Editor of the screen position of your cursor for text input position (e.g. when using Japanese/Chinese IME on Windows)
	// (default to use native imm32 api on Windows)
	void(*ImeSetInputScreenPosFn)(int x, int y);
	void* ImeWindowHandle; // = NULL // (Windows) Set this to your HWND to get automatic IME cursor positioning.

	//------------------------------------------------------------------
	// Input - Fill before calling NewFrame()
	//------------------------------------------------------------------

	ImVec2 MousePos; // Mouse position, in pixels. Set to ImVec2(-FLT_MAX,-FLT_MAX) if mouse is unavailable (on another screen, etc.)
	bool MouseDown[5]; // Mouse buttons: 0=left, 1=right, 2=middle + extras. ImGui itself mostly only uses left button (BeginPopupContext** are using right button). Others buttons allows us to track if the mouse is being used by your application + available to user as a convenience via IsMouse** API.
	float MouseWheel; // Mouse wheel Vertical: 1 unit scrolls about 5 lines text.
	float MouseWheelH; // Mouse wheel Horizontal. Most users don't have a mouse with an horizontal wheel, may not be filled by all back-ends.
	bool KeyCtrl; // Keyboard modifier pressed: Control
	bool KeyShift; // Keyboard modifier pressed: Shift
	bool KeyAlt; // Keyboard modifier pressed: Alt
	bool KeySuper; // Keyboard modifier pressed: Cmd/Super/Windows
	bool KeysDown[512]; // Keyboard keys that are pressed (ideally left in the "native" order your engine has access to keyboard keys, so you can use your own defines/enums for keys).
	ImWchar     InputCharacters[16 + 1];          // List of characters input (translated by user from keypress+keyboard state). Fill using AddInputCharacter() helper.
	float NavInputs[ImGuiNavInput_COUNT]; // Gamepad inputs. Cleared back to zero by EndFrame(). Keyboard keys will be auto-mapped and be written here by NewFrame().

	// Functions
	void AddInputCharacter(unsigned int c); // Queue new character input
	void AddInputCharacterUTF16(ImWchar16 c); // Queue new character input from an UTF-16 character, it can be a surrogate
	void AddInputCharactersUTF8(const char* str); // Queue new characters input from an UTF-8 string
	void ClearInputCharacters(); // Clear the text input buffer manually

	//------------------------------------------------------------------
	// Output - Updated by NewFrame() or EndFrame()/Render()
	// (when reading from the io.WantCaptureMouse, io.WantCaptureKeyboard flags to dispatch your inputs, it is
	// generally easier and more correct to use their state BEFORE calling NewFrame(). See FAQ for details!)
	//------------------------------------------------------------------

	bool WantCaptureMouse; // Set when Dear ImGui will use mouse inputs, in this case do not dispatch them to your main game/application (either way, always pass on mouse inputs to imgui). (e.g. unclicked mouse is hovering over an imgui window, widget is active, mouse was clicked over an imgui window, etc.).
	bool WantCaptureKeyboard; // Set when Dear ImGui will use keyboard inputs, in this case do not dispatch them to your main game/application (either way, always pass keyboard inputs to imgui). (e.g. InputText active, or an imgui window is focused and navigation is enabled, etc.).
	bool WantTextInput; // Mobile/console: when set, you may display an on-screen keyboard. This is set by Dear ImGui when it wants textual keyboard input to happen (e.g. when a InputText widget is active).
	bool WantSetMousePos; // MousePos has been altered, back-end should reposition mouse on next frame. Rarely used! Set only when ImGuiConfigFlags_NavEnableSetMousePos flag is enabled.
	bool WantSaveIniSettings; // When manual .ini load/save is active (io.IniFilename == NULL), this will be set to notify your application that you can call SaveIniSettingsToMemory() and save yourself. Important: clear io.WantSaveIniSettings yourself after saving!
	bool NavActive; // Keyboard/Gamepad navigation is currently allowed (will handle ImGuiKey_NavXXX events) = a window is focused and it doesn't use the ImGuiWindowFlags_NoNavInputs flag.
	bool NavVisible; // Keyboard/Gamepad navigation is visible and allowed (will handle ImGuiKey_NavXXX events).
	float Framerate; // Application framerate estimate, in frame per second. Solely for convenience. Rolling average estimation based on io.DeltaTime over 120 frames.
	int MetricsRenderVertices; // Vertices output during last call to Render()
	int MetricsRenderIndices; // Indices output during last call to Render() = number of triangles * 3
	int MetricsRenderWindows; // Number of visible windows
	int MetricsActiveWindows; // Number of active windows
	int MetricsActiveAllocations; // Number of active allocations, updated by MemAlloc/MemFree based on current context. May be off if you have multiple imgui contexts.
	ImVec2 MouseDelta; // Mouse delta. Note that this is zero if either current or previous position are invalid (-FLT_MAX,-FLT_MAX), so a disappearing/reappearing mouse won't have a huge delta.

	//------------------------------------------------------------------
	// [Internal] Dear ImGui will maintain those fields. Forward compatibility not guaranteed!
	//------------------------------------------------------------------

	ImGuiKeyModFlags KeyMods; // Key mods flags (same as io.KeyCtrl/KeyShift/KeyAlt/KeySuper but merged into flags), updated by NewFrame()
	ImVec2 MousePosPrev; // Previous mouse position (note that MouseDelta is not necessary == MousePos-MousePosPrev, in case either position is invalid)
	ImVec2 MouseClickedPos[5]; // Position at time of clicking
	double MouseClickedTime[5]; // Time of last click (used to figure out double-click)
	bool MouseClicked[5]; // Mouse button went from !Down to Down
	bool MouseDoubleClicked[5]; // Has mouse button been double-clicked?
	bool MouseReleased[5]; // Mouse button went from Down to !Down
	bool MouseDownOwned[5]; // Track if button was clicked inside a dear imgui window. We don't request mouse capture from the application if click started outside ImGui bounds.
	bool MouseDownWasDoubleClick[5]; // Track if button down was a double-click
	float MouseDownDuration[5]; // Duration the mouse button has been down (0.0f == just clicked)
	float MouseDownDurationPrev[5]; // Previous time the mouse button has been down
	ImVec2 MouseDragMaxDistanceAbs[5]; // Maximum distance, absolute, on each axis, of how much mouse has traveled from the clicking point
	float MouseDragMaxDistanceSqr[5]; // Squared maximum distance of how much mouse has traveled from the clicking point
	float KeysDownDuration[512]; // Duration the keyboard key has been down (0.0f == just pressed)
	float KeysDownDurationPrev[512]; // Previous duration the key has been down
	float NavInputsDownDuration[ImGuiNavInput_COUNT];
	float NavInputsDownDurationPrev[ImGuiNavInput_COUNT];
	ImWchar16 InputQueueSurrogate; // For AddInputCharacterUTF16
	ImVector<ImWchar> InputQueueCharacters; // Queue of _characters_ input (obtained by platform back-end). Fill using AddInputCharacter() helper.
	
	ImGuiIO();
};

struct ImGuiInputTextCallbackData
{
	ImGuiInputTextFlags EventFlag; // One ImGuiInputTextFlags_Callback* // Read-only
	ImGuiInputTextFlags Flags; // What user passed to InputText() // Read-only
	void* UserData; // What user passed to InputText() // Read-only

	// Arguments for the different callback events
	// - To modify the text buffer in a callback, prefer using the InsertChars() / DeleteChars() function. InsertChars() will take care of calling the resize callback if necessary.
	// - If you know your edits are not going to resize the underlying buffer allocation, you may modify the contents of 'Buf[]' directly. You need to update 'BufTextLen' accordingly (0 <= BufTextLen < BufSize) and set 'BufDirty'' to true so InputText can update its internal state.
	ImWchar EventChar; // Character input // Read-write // [CharFilter] Replace character with another one, or set to zero to drop. return 1 is equivalent to setting EventChar=0;
	ImGuiKey EventKey; // Key pressed (Up/Down/TAB) // Read-only // [Completion,History]
	char* Buf; // Text buffer // Read-write // [Resize] Can replace pointer / [Completion,History,Always] Only write to pointed data, don't replace the actual pointer!
	int BufTextLen; // Text length (in bytes) // Read-write // [Resize,Completion,History,Always] Exclude zero-terminator storage. In C land: == strlen(some_text), in C++ land: string.length()
	int BufSize; // Buffer size (in bytes) = capacity+1 // Read-only // [Resize,Completion,History,Always] Include zero-terminator storage. In C land == ARRAYSIZE(my_char_array), in C++ land: string.capacity()+1
	bool BufDirty; // Set if you modify Buf/BufTextLen! // Write // [Completion,History,Always]
	int CursorPos; // // Read-write // [Completion,History,Always]
	int SelectionStart; // // Read-write // [Completion,History,Always] == to SelectionEnd when no selection)
	int SelectionEnd; // // Read-write // [Completion,History,Always]

	// Helper functions for text manipulation.
	// Use those function to benefit from the CallbackResize behaviors. Calling those function reset the selection.
	ImGuiInputTextCallbackData();
	void DeleteChars(int pos, int bytes_count);
	void InsertChars(int pos, const char* text, const char* text_end = NULL);
	bool HasSelection() const { return SelectionStart != SelectionEnd; }
};

struct ImGuiSizeCallbackData
{
	void* UserData; // Read-only. What user passed to SetNextWindowSizeConstraints()
	ImVec2 Pos; // Read-only. Window position, for reference.
	ImVec2 CurrentSize; // Read-only. Current window size.
	ImVec2 DesiredSize; // Read-write. Desired size, based on user's mouse position. Write to this field to restrain resizing.
};

struct ImGuiPayload
{
	// Members
	void* Data; // Data (copied and owned by dear imgui)
	int DataSize; // Data size

	// [Internal]
	ImGuiID SourceId; // Source item id
	ImGuiID SourceParentId; // Source parent id (if available)
	int DataFrameCount; // Data timestamp
	char DataType[32 + 1]; // Data type tag (short user-supplied string, 32 characters max)
	bool Preview; // Set when AcceptDragDropPayload() was called and mouse has been hovering the target item (nb: handle overlapping drag targets)
	bool Delivery; // Set when AcceptDragDropPayload() was called and mouse button is released over the target item.

	ImGuiPayload() { Clear(); }
	void Clear() { SourceId = SourceParentId = 0; Data = NULL; DataSize = 0; memset(DataType, 0, sizeof(DataType)); DataFrameCount = -1; Preview = Delivery = false; }
	bool IsDataType(const char* type) const { return DataFrameCount != -1 && strcmp(type, DataType) == 0; }
	bool IsPreview() const { return Preview; }
	bool IsDelivery() const { return Delivery; }
};

namespace ImGui
{
	static inline void TreeAdvanceToLabelPos() { SetCursorPosX(GetCursorPosX() + GetTreeNodeToLabelSpacing()); }
	static inline void SetNextTreeNodeOpen(bool open, ImGuiCond cond = 0) { SetNextItemOpen(open, cond); }
	static inline float GetContentRegionAvailWidth() { return GetContentRegionAvail().x; }
	static inline ImDrawList* GetOverlayDrawList() { return GetForegroundDrawList(); }
	static inline void SetScrollHere(float center_ratio = 0.5f) { SetScrollHereY(center_ratio); }
	static inline bool IsItemDeactivatedAfterChange() { return IsItemDeactivatedAfterEdit(); }
	bool InputFloat(const char* label, float* v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags flags = 0); // Use the 'const char* format' version instead of 'decimal_precision'!
	bool InputFloat2(const char* label, float v[2], int decimal_precision, ImGuiInputTextFlags flags = 0);
	bool InputFloat3(const char* label, float v[3], int decimal_precision, ImGuiInputTextFlags flags = 0);
	bool InputFloat4(const char* label, float v[4], int decimal_precision, ImGuiInputTextFlags flags = 0);
	static inline bool IsAnyWindowFocused() { return IsWindowFocused(ImGuiFocusedFlags_AnyWindow); }
	static inline bool IsAnyWindowHovered() { return IsWindowHovered(ImGuiHoveredFlags_AnyWindow); }
	static inline ImVec2 CalcItemRectClosestPoint(const ImVec2& pos, bool on_edge = false, float outward = 0.f) { return pos; }
}

typedef ImGuiInputTextCallback ImGuiTextEditCallback;

typedef ImGuiInputTextCallbackData ImGuiTextEditCallbackData;

struct ImGuiOnceUponAFrame
{
	ImGuiOnceUponAFrame() { RefFrame = -1; }
	mutable int RefFrame;
	operator bool() const { int current_frame = ImGui::GetFrameCount(); if (RefFrame == current_frame) return false; RefFrame = current_frame; return true; }
};

struct ImGuiTextFilter
{
	ImGuiTextFilter(const char* default_filter = "");

	bool Draw(const char* label = "Filter (inc,-exc)", float width = 0.0f);

	bool PassFilter(const char* text, const char* text_end = NULL) const;

	void Build();

	void Clear() { InputBuf[0] = 0; Build(); }

	bool IsActive() const { return !Filters.empty(); }

	struct ImGuiTextRange
	{
		const char* b;
		const char* e;

		ImGuiTextRange() { b = e = NULL; }
		ImGuiTextRange(const char* _b, const char* _e) { b = _b; e = _e; }
		bool empty() const { return b == e; }
		void split(char separator, ImVector<ImGuiTextRange>* out) const;
	};
	char InputBuf[256];
	ImVector<ImGuiTextRange>Filters;
	int CountGrep;
};

struct ImGuiTextBuffer
{
	ImVector<char> Buf;
	static char EmptyString[1];

	ImGuiTextBuffer() { }
	inline char operator[](int i) const { return Buf.Data[i]; }
	const char* begin() const { return Buf.Data ? &Buf.front() : EmptyString; }
	const char* end() const { return Buf.Data ? &Buf.back() : EmptyString; } // Buf is zero-terminated, so end() will point on the zero-terminator
	int size() const { return Buf.Size ? Buf.Size - 1 : 0; }
	bool empty() const { return Buf.Size <= 1; }
	void clear() { Buf.clear(); }
	void reserve(int capacity) { Buf.reserve(capacity); }
	const char* c_str() const { return Buf.Data ? Buf.Data : EmptyString; }
	void append(const char* str, const char* str_end = NULL);
	void appendf(const char* fmt, ...);
	void appendfv(const char* fmt, va_list args);
};

struct ImGuiStorage
{
	struct ImGuiStoragePair
	{
		ImGuiID key;
		union { int val_i; float val_f; void* val_p; };
		ImGuiStoragePair(ImGuiID _key, int _val_i) { key = _key; val_i = _val_i; }
		ImGuiStoragePair(ImGuiID _key, float _val_f) { key = _key; val_f = _val_f; }
		ImGuiStoragePair(ImGuiID _key, void* _val_p) { key = _key; val_p = _val_p; }
	};

	ImVector<ImGuiStoragePair> Data;

	void Clear() { Data.clear(); }
	int GetInt(ImGuiID key, int default_val = 0) const;
	void SetInt(ImGuiID key, int val);
	bool GetBool(ImGuiID key, bool default_val = false) const;
	void SetBool(ImGuiID key, bool val);
	float GetFloat(ImGuiID key, float default_val = 0.0f) const;
	void SetFloat(ImGuiID key, float val);
	void* GetVoidPtr(ImGuiID key) const; // default_val is NULL
	void SetVoidPtr(ImGuiID key, void* val);

	int* GetIntRef(ImGuiID key, int default_val = 0);
	bool* GetBoolRef(ImGuiID key, bool default_val = false);
	float* GetFloatRef(ImGuiID key, float default_val = 0.0f);
	void** GetVoidPtrRef(ImGuiID key, void* default_val = NULL);

	// Use on your own storage if you know only integer are being stored (open/close all tree nodes)
	void SetAllInt(int val);

	// For quicker full rebuild of a storage (instead of an incremental one), you may add all your contents and then sort once.
	void BuildSortByKey();
};

struct ImGuiListClipper
{
	int DisplayStart, DisplayEnd;
	int ItemsCount;

	// [Internal]
	int StepNo;
	float ItemsHeight;
	float StartPosY;

	// items_count: Use -1 to ignore (you can call Begin later). Use INT_MAX if you don't know how many items you have (in which case the cursor won't be advanced in the final step).
	// items_height: Use -1.0f to be calculated automatically on first step. Otherwise pass in the distance between your items, typically GetTextLineHeightWithSpacing() or GetFrameHeightWithSpacing().
	// If you don't specify an items_height, you NEED to call Step(). If you specify items_height you may call the old Begin()/End() api directly, but prefer calling Step().
	ImGuiListClipper(int items_count = -1, float items_height = -1.0f) { Begin(items_count, items_height); } // NB: Begin() initialize every fields (as we allow user to call Begin/End multiple times on a same instance if they want).
	~ImGuiListClipper() { } // Assert if user forgot to call End() or Step() until false.

	bool Step(); // Call until it returns false. The DisplayStart/DisplayEnd fields will be set and you can process/draw those items.
	void Begin(int items_count, float items_height = -1.0f); // Automatically called by constructor if you passed 'items_count' or by Step() in Step 1.
	void End(); // Automatically called on the last call of Step() that returns false.
};

#define IM_COL32_R_SHIFT 0
#define IM_COL32_G_SHIFT 8
#define IM_COL32_B_SHIFT 16
#define IM_COL32_A_SHIFT 24
#define IM_COL32_A_MASK 0xFF000000
#define IM_COL32(R,G,B,A) (((ImU32)(A)<<IM_COL32_A_SHIFT) | ((ImU32)(B)<<IM_COL32_B_SHIFT) | ((ImU32)(G)<<IM_COL32_G_SHIFT) | ((ImU32)(R)<<IM_COL32_R_SHIFT))
#define IM_COL32_WHITE IM_COL32(255,255,255,255) // Opaque white = 0xFFFFFFFF
#define IM_COL32_BLACK IM_COL32(0,0,0,255) // Opaque black
#define IM_COL32_BLACK_TRANS IM_COL32(0,0,0,0) // Transparent black = 0x00000000

struct ImColor
{
	ImVec4 Value;

	ImColor() { Value.x = Value.y = Value.z = Value.w = 0.0f; }
	ImColor(int r, int g, int b, int a = 255) { float sc = 1.0f / 255.0f; Value.x = (float)r * sc; Value.y = (float)g * sc; Value.z = (float)b * sc; Value.w = (float)a * sc; }
	ImColor(ImU32 rgba) { float sc = 1.0f / 255.0f; Value.x = (float)((rgba >> IM_COL32_R_SHIFT) & 0xFF) * sc; Value.y = (float)((rgba >> IM_COL32_G_SHIFT) & 0xFF) * sc; Value.z = (float)((rgba >> IM_COL32_B_SHIFT) & 0xFF) * sc; Value.w = (float)((rgba >> IM_COL32_A_SHIFT) & 0xFF) * sc; }
	ImColor(float r, float g, float b, float a = 1.0f) { Value.x = r; Value.y = g; Value.z = b; Value.w = a; }
	ImColor(const ImVec4& col) { Value = col; }
	inline operator ImU32() const { return ImGui::ColorConvertFloat4ToU32(Value); }
	inline operator ImVec4() const { return Value; }

	// FIXME-OBSOLETE: May need to obsolete/cleanup those helpers.
	inline void SetHSV(float h, float s, float v, float a = 1.0f) { ImGui::ColorConvertHSVtoRGB(h, s, v, Value.x, Value.y, Value.z); Value.w = a; }
	static ImColor HSV(float h, float s, float v, float a = 1.0f) { float r, g, b; ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b); return ImColor(r, g, b, a); }
};

typedef void(*ImDrawCallback)(const ImDrawList* parent_list, const ImDrawCmd* cmd);

#define ImDrawCallback_ResetRenderState (ImDrawCallback)(-1)

struct ImDrawCmd
{
	unsigned int ElemCount; // Number of indices (multiple of 3) to be rendered as triangles. Vertices are stored in the callee ImDrawList's vtx_buffer[] array, indices in idx_buffer[].
	ImVec4 ClipRect; // Clipping rectangle (x1, y1, x2, y2). Subtract ImDrawData->DisplayPos to get clipping rectangle in "viewport" coordinates
	ImTextureID TextureId; // User-provided texture ID. Set by user in ImfontAtlas::SetTexID() for fonts or passed to Image*() functions. Ignore if never using images or multiple fonts atlas.
	unsigned int VtxOffset; // Start offset in vertex buffer. Pre-1.71 or without ImGuiBackendFlags_RendererHasVtxOffset: always 0. With ImGuiBackendFlags_RendererHasVtxOffset: may be >0 to support meshes larger than 64K vertices with 16-bit indices.
	unsigned int IdxOffset; // Start offset in index buffer. Always equal to sum of ElemCount drawn so far.
	ImDrawCallback UserCallback; // If != NULL, call the function instead of rendering the vertices. clip_rect and texture_id will be set normally.
	void* UserCallbackData; // The draw callback code can access this.

	ImDrawCmd() { ElemCount = 0; TextureId = (ImTextureID)NULL; VtxOffset = IdxOffset = 0; UserCallback = NULL; UserCallbackData = NULL; }
};

typedef unsigned short ImDrawIdx;

struct ImDrawVert
{
	ImVec2 pos;
	ImVec2 uv;
	ImU32 col;
};

struct ImDrawChannel
{
	ImVector<ImDrawCmd> _CmdBuffer;
	ImVector<ImDrawIdx> _IdxBuffer;
};

struct ImDrawListSplitter
{
	int _Current; // Current channel number (0)
	int _Count; // Number of active channels (1+)
	ImVector<ImDrawChannel> _Channels; // Draw channels (not resized down so _Count might be < Channels.Size)

	inline ImDrawListSplitter() { Clear(); }
	inline ~ImDrawListSplitter() { ClearFreeMemory(); }
	inline void Clear() { _Current = 0; _Count = 1; } // Do not clear Channels[] so our allocations are reused next frame
	void ClearFreeMemory();
	void Split(ImDrawList* draw_list, int count);
	void Merge(ImDrawList* draw_list);
	void SetCurrentChannel(ImDrawList* draw_list, int channel_idx);
};

enum ImDrawCornerFlags_
{
	ImDrawCornerFlags_None = 0,
	ImDrawCornerFlags_TopLeft = 1 << 0, // 0x1
	ImDrawCornerFlags_TopRight = 1 << 1, // 0x2
	ImDrawCornerFlags_BotLeft = 1 << 2, // 0x4
	ImDrawCornerFlags_BotRight = 1 << 3, // 0x8
	ImDrawCornerFlags_Top = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight, // 0x3
	ImDrawCornerFlags_Bot = ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight, // 0xC
	ImDrawCornerFlags_Left = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotLeft, // 0x5
	ImDrawCornerFlags_Right = ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight, // 0xA
	ImDrawCornerFlags_All = 0xF // In your function calls you may use ~0 (= all bits sets) instead of ImDrawCornerFlags_All, as a convenience
};

enum ImDrawListFlags_
{
	ImDrawListFlags_None = 0,
	ImDrawListFlags_AntiAliasedLines = 1 << 0, // Lines are anti-aliased (*2 the number of triangles for 1.0f wide line, otherwise *3 the number of triangles)
	ImDrawListFlags_AntiAliasedFill = 1 << 1, // Filled shapes have anti-aliased edges (*2 the number of vertices)
	ImDrawListFlags_AllowVtxOffset = 1 << 2 // Can emit 'VtxOffset > 0' to allow large meshes. Set when 'ImGuiBackendFlags_RendererHasVtxOffset' is enabled.
};

struct ImDrawList
{
	// This is what you have to render
	ImVector<ImDrawCmd> CmdBuffer; // Draw commands. Typically 1 command = 1 GPU draw call, unless the command is a callback.
	ImVector<ImDrawIdx> IdxBuffer; // Index buffer. Each command consume ImDrawCmd::ElemCount of those
	ImVector<ImDrawVert> VtxBuffer; // Vertex buffer.
	ImDrawListFlags Flags; // Flags, you may poke into these to adjust anti-aliasing settings per-primitive.

	// [Internal, used while building lists]
	const ImDrawListSharedData* _Data; // Pointer to shared draw data (you can use ImGui::GetDrawListSharedData() to get the one from current ImGui context)
	const char* _OwnerName; // Pointer to owner window's name for debugging
	unsigned int _VtxCurrentOffset; // [Internal] Always 0 unless 'Flags & ImDrawListFlags_AllowVtxOffset'.
	unsigned int _VtxCurrentIdx; // [Internal] Generally == VtxBuffer.Size unless we are past 64K vertices, in which case this gets reset to 0.
	ImDrawVert* _VtxWritePtr; // [Internal] point within VtxBuffer.Data after each add command (to avoid using the ImVector<> operators too much)
	ImDrawIdx* _IdxWritePtr; // [Internal] point within IdxBuffer.Data after each add command (to avoid using the ImVector<> operators too much)
	ImVector<ImVec4> _ClipRectStack; // [Internal]
	ImVector<ImTextureID> _TextureIdStack; // [Internal]
	ImVector<ImVec2> _Path; // [Internal] current path building
	ImDrawListSplitter _Splitter; // [Internal] for channels api

	// If you want to create ImDrawList instances, pass them ImGui::GetDrawListSharedData() or create and use your own ImDrawListSharedData (so you can use ImDrawList without ImGui)
	ImDrawList(const ImDrawListSharedData* shared_data) { _Data = shared_data; _OwnerName = NULL; Clear(); }
	~ImDrawList() { ClearFreeMemory(); }
	void PushClipRect(ImVec2 clip_rect_min, ImVec2 clip_rect_max, bool intersect_with_current_clip_rect = false); // Render-level scissoring. This is passed down to your render function but not used for CPU-side coarse clipping. Prefer using higher-level ImGui::PushClipRect() to affect logic (hit-testing and widget culling)
	void PushClipRectFullScreen();
	void PopClipRect();
	void PushTextureID(ImTextureID texture_id);
	void PopTextureID();
	inline ImVec2 GetClipRectMin() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.x, cr.y); }
	inline ImVec2 GetClipRectMax() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.z, cr.w); }

	// Primitives
	// - For rectangular primitives, "p_min" and "p_max" represent the upper-left and lower-right corners.
	// - For circle primitives, use "num_segments == 0" to automatically calculate tessellation (preferred).
	// In future versions we will use textures to provide cheaper and higher-quality circles.
	// Use AddNgon() and AddNgonFilled() functions if you need to guaranteed a specific number of sides.
	void AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f);
	void AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All, float thickness = 1.0f); // a: upper-left, b: lower-right (== upper-left + size), rounding_corners_flags: 4 bits corresponding to which corner to round
	void AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All); // a: upper-left, b: lower-right (== upper-left + size)
	void AddRectFilledMultiColor(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
	void AddQuad(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness = 1.0f);
	void AddQuadFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col);
	void AddTriangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness = 1.0f);
	void AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col);
	void AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments = 12, float thickness = 1.0f);
	void AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments = 12);
	void AddNgon(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
	void AddNgonFilled(const ImVec2& center, float radius, ImU32 col, int num_segments);
	void AddTextEx(const ImVec2& pos, float font_size, ImU32 col, const char* text_begin, const char* text_end = NULL);
	void AddTextEx(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
	void AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL);
	void AddText(const ImVec2& pos, float font_size, ImU32 col, const char* text_begin, const char* text_end = NULL);
	void AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
	void AddPolyline(const ImVec2* points, int num_points, ImU32 col, bool closed, float thickness);
	void AddConvexPolyFilled(const ImVec2* points, int num_points, ImU32 col); // Note: Anti-aliased filling requires points to be in clockwise order.
	void AddBezierCurve(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0);

	// Image primitives
	// - Read FAQ to understand what ImTextureID is.
	// - "p_min" and "p_max" represent the upper-left and lower-right corners of the rectangle.
	// - "uv_min" and "uv_max" represent the normalized texture coordinates to use for those corners. Using (0,0)->(1,1) texture coordinates will generally display the entire texture.
	void AddImage(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min = ImVec2(0, 0), const ImVec2& uv_max = ImVec2(1, 1), ImU32 col = IM_COL32_WHITE);
	void AddImageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1 = ImVec2(0, 0), const ImVec2& uv2 = ImVec2(1, 0), const ImVec2& uv3 = ImVec2(1, 1), const ImVec2& uv4 = ImVec2(0, 1), ImU32 col = IM_COL32_WHITE);
	void AddImageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding, ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All);

	// Stateful path API, add points then finish with PathFillConvex() or PathStroke()
	inline void PathClear() { _Path.Size = 0; }
	inline void PathLineTo(const ImVec2& pos) { _Path.push_back(pos); }
	inline void PathLineToMergeDuplicate(const ImVec2& pos) { if (_Path.Size == 0 || memcmp(&_Path.Data[_Path.Size - 1], &pos, 8) != 0) _Path.push_back(pos); }
	inline void PathFillConvex(ImU32 col) { AddConvexPolyFilled(_Path.Data, _Path.Size, col); _Path.Size = 0; } // Note: Anti-aliased filling requires points to be in clockwise order.
	inline void PathStroke(ImU32 col, bool closed, float thickness = 1.0f) { AddPolyline(_Path.Data, _Path.Size, col, closed, thickness); _Path.Size = 0; }
	void PathArcTo(const ImVec2& center, float radius, float a_min, float a_max, int num_segments = 10);
	void PathArcToFast(const ImVec2& center, float radius, int a_min_of_12, int a_max_of_12); // Use precomputed angles for a 12 steps circle
	void PathBezierCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments = 0);
	void PathRect(const ImVec2& rect_min, const ImVec2& rect_max, float rounding = 0.0f, ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All);

	// Advanced
	void AddCallback(ImDrawCallback callback, void* callback_data); // Your rendering function must check for 'UserCallback' in ImDrawCmd and call the function instead of rendering triangles.
	void AddDrawCmd(); // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering / blending). Otherwise primitives are merged into the same draw-call as much as possible
	ImDrawList* CloneOutput() const; // Create a clone of the CmdBuffer/IdxBuffer/VtxBuffer.

	// Advanced: Channels
	// - Use to split render into layers. By switching channels to can render out-of-order (e.g. submit FG primitives before BG primitives)
	// - Use to minimize draw calls (e.g. if going back-and-forth between multiple clipping rectangles, prefer to append into separate channels then merge at the end)
	// - FIXME-OBSOLETE: This API shouldn't have been in ImDrawList in the first place!
	// Prefer using your own persistent copy of ImDrawListSplitter as you can stack them.
	// Using the ImDrawList::ChannelsXXXX you cannot stack a split over another.
	inline void ChannelsSplit(int count) { _Splitter.Split(this, count); }
	inline void ChannelsMerge() { _Splitter.Merge(this); }
	inline void ChannelsSetCurrent(int n) { _Splitter.SetCurrentChannel(this, n); }

	// Internal helpers
	// NB: all primitives needs to be reserved via PrimReserve() beforehand!
	void Clear();
	void ClearFreeMemory();
	void PrimReserve(int idx_count, int vtx_count);
	void PrimUnreserve(int idx_count, int vtx_count);
	void PrimRect(const ImVec2& a, const ImVec2& b, ImU32 col); // Axis aligned rectangle (composed of two triangles)
	void PrimRectUV(const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col);
	void PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col);
	inline void PrimWriteVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { _VtxWritePtr->pos = pos; _VtxWritePtr->uv = uv; _VtxWritePtr->col = col; _VtxWritePtr++; _VtxCurrentIdx++; }
	inline void PrimWriteIdx(ImDrawIdx idx) { *_IdxWritePtr = idx; _IdxWritePtr++; }
	inline void PrimVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { PrimWriteIdx((ImDrawIdx)_VtxCurrentIdx); PrimWriteVtx(pos, uv, col); }
	void UpdateClipRect();
	void UpdateTextureID();
};

struct ImDrawData
{
	ImDrawList** CmdLists; // Array of ImDrawList* to render. The ImDrawList are owned by ImGuiContext and only pointed to from here.
	ImVec2 DisplayPos; // Upper-left position of the viewport to render (== upper-left of the orthogonal projection matrix to use)
	ImVec2 DisplaySize; // Size of the viewport to render (== io.DisplaySize for the main viewport) (DisplayPos + DisplaySize == lower-right of the orthogonal projection matrix to use)
	ImVec2 FramebufferScale; // Amount of pixels for each unit of DisplaySize. Based on io.DisplayFramebufferScale. Generally (1,1) on normal display, (2,2) on OSX with Retina display.

	bool Valid; // Only valid after Render() is called and before the next NewFrame() is called.
	int CmdListsCount; // Number of ImDrawList* to render
	int TotalIdxCount; // For convenience, sum of all ImDrawList's IdxBuffer.Size
	int TotalVtxCount; // For convenience, sum of all ImDrawList's VtxBuffer.Size

	// Functions
	ImDrawData() { Valid = false; Clear(); }
	~ImDrawData() { Clear(); }
	void Clear() { Valid = false; CmdLists = NULL; CmdListsCount = TotalVtxCount = TotalIdxCount = 0; DisplayPos = DisplaySize = FramebufferScale = ImVec2(0.f, 0.f); } // The ImDrawList are owned by ImGuiContext!
	
	void DeIndexAllBuffers(); // Helper to convert all buffers from indexed to non-indexed, in case you cannot render indexed. Note: this is slow and most likely a waste of resources. Always prefer indexed rendering!
	void ScaleClipRects(const ImVec2& fb_scale); // Helper to scale the ClipRect field of each ImDrawCmd. Use if your final output buffer is at a different scale than Dear ImGui expects, or if there is a difference between your window resolution and framebuffer resolution.
};

struct ImFontConfig
{
	char Name[64];
	ImFont* DstFont;
	ImVec2 GlyphExtraSpacing;
	ImVec2 GlyphOffset;
	void* FontData;
	int FontDataSize;
	bool FontDataOwnedByAtlas;
	int FontNo;
	float SizePixels;
	int OversampleH;
	int OversampleV;
	float GlyphMinAdvanceX;
	float GlyphMaxAdvanceX;
	bool PixelSnapH;
	const ImWchar* GlyphRanges;
	bool MergeMode;
	unsigned int RasterizerFlags;
	float RasterizerMultiply;
	ImWchar EllipsisChar;
	ImFontConfig();
};

struct ImFontGlyph
{
	float AdvanceX; // Distance to next character (= data from font + ImFontConfig::GlyphExtraSpacing.x baked in)
	float X0, Y0, X1, Y1; // Glyph corners
	float U0, V0, U1, V1; // Texture coordinates
	unsigned int Codepoint : 31; // 0x0000..0xFFFF
	unsigned int Visible : 1; // Flag to allow early out when rendering
};

struct ImFontGlyphRangesBuilder
{
	ImVector<ImU32> UsedChars; // Store 1-bit per Unicode code point (0=unused, 1=used)

	ImFontGlyphRangesBuilder() { Clear(); }
	inline void Clear() { int size_in_bytes = (0xFFFF + 1) / 8; UsedChars.resize(size_in_bytes / (int)sizeof(ImU32)); memset(UsedChars.Data, 0, (size_t)size_in_bytes); }
	inline bool GetBit(size_t n) const { int off = (int)(n >> 5); ImU32 mask = 1u << (n & 31); return (UsedChars[off] & mask) != 0; } // Get bit n in the array
	inline void SetBit(size_t n) { int off = (int)(n >> 5); ImU32 mask = 1u << (n & 31); UsedChars[off] |= mask; } // Set bit n in the array
	inline void AddChar(ImWchar c) { SetBit(c); } // Add character
	void AddText(const char* text, const char* text_end = NULL); // Add string (each character of the UTF-8 string are added)
	void AddRanges(const ImWchar* ranges); // Add ranges, e.g. builder.AddRanges(ImFontAtlas::GetGlyphRangesDefault()) to force add all of ASCII/Latin+Ext
	void BuildRanges(ImVector<ImWchar>* out_ranges); // Output new ranges
};

struct ImFontAtlasCustomRect
{
	unsigned int ID; // Input // User ID. Use < 0x110000 to map into a font glyph, >= 0x110000 for other/internal/custom texture data.
	unsigned short X, Y; // Output // Packed position in Atlas
	unsigned short Width, Height; // Input // Desired rectangle dimension
	float GlyphAdvanceX; // Input // For custom font glyphs only (ID < 0x110000): glyph xadvance
	ImVec2 GlyphOffset; // Input // For custom font glyphs only (ID < 0x110000): glyph display offset
	ImFont* Font; // Input // For custom font glyphs only (ID < 0x110000): target font
	ImFontAtlasCustomRect() { ID = 0xFFFFFFFF; Width = Height = 0; X = Y = 0xFFFF; GlyphAdvanceX = 0.0f; GlyphOffset = ImVec2(0, 0); Font = NULL; }
	bool IsPacked() const { return X != 0xFFFF; }
};

enum ImFontAtlasFlags_
{
	ImFontAtlasFlags_None = 0,
	ImFontAtlasFlags_NoPowerOfTwoHeight = 1 << 0, // Don't round the height to next power of two
	ImFontAtlasFlags_NoMouseCursors = 1 << 1 // Don't build software mouse cursors into the atlas
};

struct ImFontAtlas
{
	ImFontAtlas();
	~ImFontAtlas();
	ImFont* AddFont(const ImFontConfig* font_cfg);
	ImFont* AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
	ImFont* AddFontFromMemoryTTF(void* font_data, int font_size, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL); // Note: Transfer ownership of 'ttf_data' to ImFontAtlas! Will be deleted after destruction of the atlas. Set font_cfg->FontDataOwnedByAtlas=false to keep ownership of your data and it won't be freed.
	void ClearInputData(); // Clear input data (all ImFontConfig structures including sizes, TTF data, glyph ranges, etc.) = all the data used to build the texture and fonts.
	void ClearTexData(); // Clear output font data (glyphs storage, UV coordinates).
	void ClearFonts(); // Clear output font data (glyphs storage, UV coordinates).
	void Clear(); // Clear all input and output.

	// Build atlas, retrieve pixel data.
	// User is in charge of copying the pixels into graphics memory (e.g. create a texture with your engine). Then store your texture handle with SetTexID().
	// The pitch is always = Width * BytesPerPixels (1 or 4)
	// Building in RGBA32 format is provided for convenience and compatibility, but note that unless you manually manipulate or copy color data into
	// the texture (e.g. when using the AddCustomRect*** api), then the RGB pixels emitted will always be white (~75% of memory/bandwidth waste.
	bool Build(); // Build pixels data. This is called automatically for you by the GetTexData*** functions.
	void GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL); // 1 byte per-pixel
	void GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL); // 4 bytes-per-pixel
	bool IsBuilt() const { return Fonts.Size > 0 && (TexPixelsAlpha8 != NULL || TexPixelsRGBA32 != NULL); }
	void SetTexID(ImTextureID id) { TexID = id; }

	//-------------------------------------------
	// Glyph Ranges
	//-------------------------------------------
	const ImWchar* GetGlyphRangesChineseFull();

	//-------------------------------------------
	// [BETA] Custom Rectangles/Glyphs API
	//-------------------------------------------

	// You can request arbitrary rectangles to be packed into the atlas, for your own purposes.
	// After calling Build(), you can query the rectangle position and render your pixels.
	// You can also request your rectangles to be mapped as font glyph (given a font + Unicode point),
	// so you can render e.g. custom colorful icons and use them as regular glyphs.
	// Read docs/FONTS.txt for more details about using colorful icons.
	int AddCustomRectRegular(unsigned int id, int width, int height); // Id needs to be >= 0x110000. Id >= 0x80000000 are reserved for ImGui and ImDrawList
	int AddCustomRectFontGlyph(ImFont* font, ImWchar id, int width, int height, float advance_x, const ImVec2& offset = ImVec2(0, 0)); // Id needs to be < 0x110000 to register a rectangle to map into a specific font.

	// [Internal]
	void CalcCustomRectUV(const ImFontAtlasCustomRect* rect, ImVec2* out_uv_min, ImVec2* out_uv_max) const;
	bool GetMouseCursorTexData(ImGuiMouseCursor cursor, ImVec2* out_offset, ImVec2* out_size, ImVec2 out_uv_border[2], ImVec2 out_uv_fill[2]);

	//-------------------------------------------
	// Members
	//-------------------------------------------

	unsigned char* TexPixelsAlpha8; // 1 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight
	unsigned int* TexPixelsRGBA32; // 4 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight * 4
	int TexWidth; // Texture width calculated during Build().
	int TexHeight; // Texture height calculated during Build().
	ImVec2 TexUvScale; // = (1.0f/TexWidth, 1.0f/TexHeight)
	ImVec2 TexUvWhitePixel; // Texture coordinates to a white pixel
	ImVector<ImFont*> Fonts; // Hold all the fonts returned by AddFont*. Fonts[0] is the default font upon calling ImGui::NewFrame(), use ImGui::PushFont()/PopFont() to change the current font.
	ImVector<ImFontAtlasCustomRect> CustomRects; // Rectangles for packing custom texture data into the atlas.
	ImVector<ImFontConfig> ConfigData; // Internal data
	int CustomRectIds[1]; // Identifiers of custom texture rectangle used by ImFontAtlas/ImDrawList
	typedef ImFontAtlasCustomRect CustomRect; // OBSOLETED in 1.72+
	typedef ImFontGlyphRangesBuilder GlyphRangesBuilder; // OBSOLETED in 1.67+

	bool Locked; // Marked as Locked by ImGui::NewFrame() so attempt to modify the atlas will assert.
	ImFontAtlasFlags Flags; // Build flags (see ImFontAtlasFlags_)
	ImTextureID TexID; // User data to refer to the texture once it has been uploaded to user's graphic systems. It is passed back to you during rendering via the ImDrawCmd structure.
	int TexDesiredWidth; // Texture width desired by user before Build(). Must be a power-of-two. If have many glyphs your graphics API have texture size restrictions you may want to increase texture width to decrease height.
	int TexGlyphPadding; // Padding between glyphs within texture in pixels. Defaults to 1. If your rendering method doesn't rely on bilinear filtering you may set this to 0.
};

struct ImFont
{
	// Members: Cold ~32/40 bytes
	ImFontAtlas* ContainerAtlas; // 4-8 // out // // What we has been loaded into
	const ImFontConfig* ConfigData; // 4-8 // in // // Pointer within ContainerAtlas->ConfigData
	short ConfigDataCount; // 2 // in // ~ 1 // Number of ImFontConfig involved in creating this font. Bigger than 1 when merging multiple font sources into one ImFont.
	ImWchar FallbackChar; // 2 // in // = '?' // Replacement character if a glyph isn't found. Only set via SetFallbackChar()
	ImWchar EllipsisChar; // 2 // out // = -1 // Character used for ellipsis rendering.
	bool DirtyLookupTables; // 1 // out //
	float Scale; // 4 // in // = 1.f // Base font scale, multiplied by the per-window font scale which you can adjust with SetWindowFontScale()
	float Ascent, Descent; // 4+4 // out // // Ascent: distance from top to bottom of e.g. 'A' [0..FontSize]
	int MetricsTotalSurface;// 4 // out // // Total surface in pixels to get an idea of the font rasterization/texture cost (not exact, we approximate the cost of padding between glyphs)
	ImU8 Used4kPagesMap[(0xFFFF + 1) / 4096 / 8]; // 2 bytes if ImWchar=ImWchar16, 34 bytes if ImWchar==ImWchar32. Store 1-bit for each block of 4K codepoints that has one active glyph. This is mainly used to facilitate iterations accross all used codepoints.

	// Members: Hot ~20/24 bytes (for CalcTextSize)
	float FontSize; // 4 // in // // Height of characters/line, set during loading (don't change after loading)
	float FallbackAdvanceX; // 4 // out // = FallbackGlyph->AdvanceX
	ImVector<float> IndexAdvanceX; // 12-16 // out // // Sparse. Glyphs->AdvanceX in a directly indexable way (cache-friendly for CalcTextSize functions which only this this info, and are often bottleneck in large UI).
	// Members: Hot ~36/48 bytes (for CalcTextSize + render loop)
	ImVector<ImWchar> IndexLookup; // 12-16 // out // // Sparse. Index glyphs by Unicode code-point.
	ImVector<ImFontGlyph> Glyphs; // 12-16 // out // // All glyphs.
	const ImFontGlyph* FallbackGlyph; // 4-8 // out // = FindGlyph(FontFallbackChar)
	ImVec2 DisplayOffset; // 8 // in // = (0,0) // Offset font rendering by xx pixels

	// Methods
	ImFont();
	~ImFont();
	const ImFontGlyph*FindGlyph(ImWchar c) const;
	const ImFontGlyph*FindGlyphNoFallback(ImWchar c) const;
	float GetCharAdvance(ImWchar c) const { return ((int)c < IndexAdvanceX.Size) ? IndexAdvanceX[(int)c] : FallbackAdvanceX; }

	// 'max_width' stops rendering after a certain width (could be turned into a 2d size). FLT_MAX to disable.
	// 'wrap_width' enable automatic word-wrapping across multiple lines to fit into given width. 0.0f to disable.
	ImVec2 CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = NULL, const char** remaining = NULL) const; // utf8
	const char* CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const;
	void RenderChar(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, ImWchar c) const;
	void RenderText(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width = 0.0f, bool cpu_fine_clip = false) const;

	// [Internal] Don't use!
	void BuildLookupTable();
	void ClearOutputData();
	void GrowIndex(int new_size);
	void AddGlyph(ImWchar c, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float advance_x);
	void AddRemapChar(ImWchar dst, ImWchar src, bool overwrite_dst = true); // Makes 'dst' character/glyph points to 'src' character/glyph. Currently needs to be called AFTER fonts have been built.
	void SetGlyphVisible(ImWchar c, bool visible);
	void SetFallbackChar(ImWchar c);
	bool IsGlyphRangeUnused(unsigned int c_begin, unsigned int c_last);
};
