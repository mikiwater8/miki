#include "stdafx.h"

bool g_MenuEnable = true;

bool g_ImplWin32Init = false;

signed __int64 g_Time = 0;

signed __int64 g_TicksPerSecond = 0;

WNDPROC g_OriginalWndProc = NULL;

D3DPRESENT_PARAMETERS g_d3dPresent = { NULL };

bool ImGui_ImplWin32_Init()
{
	if (g_ImplWin32Init == true)
	{
		return true;
	}
	else
	{
		if (g_pd3dSwapChain && g_pd3dSwapChain->GetPresentParameters(&g_d3dPresent) == S_OK)
		{
			ImGuiIO& io = ImGui::GetIO();

			io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

			io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

			io.ImeWindowHandle = g_d3dPresent.hDeviceWindow;

			io.KeyMap[ImGuiKey_Tab] = VK_TAB;

			io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;

			io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;

			io.KeyMap[ImGuiKey_UpArrow] = VK_UP;

			io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;

			io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;

			io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;

			io.KeyMap[ImGuiKey_Home] = VK_HOME;

			io.KeyMap[ImGuiKey_End] = VK_END;

			io.KeyMap[ImGuiKey_Insert] = VK_INSERT;

			io.KeyMap[ImGuiKey_Delete] = VK_DELETE;

			io.KeyMap[ImGuiKey_Backspace] = VK_BACK;

			io.KeyMap[ImGuiKey_Space] = VK_SPACE;

			io.KeyMap[ImGuiKey_Enter] = VK_RETURN;

			io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;

			io.KeyMap[ImGuiKey_KeyPadEnter] = VK_RETURN;

			io.KeyMap[ImGuiKey_A] = 'A';

			io.KeyMap[ImGuiKey_C] = 'C';

			io.KeyMap[ImGuiKey_V] = 'V';

			io.KeyMap[ImGuiKey_X] = 'X';

			io.KeyMap[ImGuiKey_Y] = 'Y';

			io.KeyMap[ImGuiKey_Z] = 'Z';

			QueryPerformanceCounter((LARGE_INTEGER *)&g_Time);

			QueryPerformanceFrequency((LARGE_INTEGER *)&g_TicksPerSecond);

			if (g_OriginalWndProc == NULL)
			{
				g_OriginalWndProc = (WNDPROC)SetWindowLongPtrA(g_d3dPresent.hDeviceWindow, -4, (ULONG_PTR)ImGui_ImplWin32_WndProcHandler);
			}

			g_ImplWin32Init = true;
		}
	}

	return false;
}

void ImGui_ImplWin32_Shutdown()
{
	g_Time = 0;

	g_TicksPerSecond = 0;

	RtlSecureZeroMemory(&g_d3dPresent, sizeof(g_d3dPresent));

	g_ImplWin32Init = false;
}

void ImGui_ImplWin32_NewFrame()
{
	ImGuiIO& io = ImGui::GetIO();

	INT64 CurrentTime;

	POINT CursorPos;

	if (QueryPerformanceCounter((LARGE_INTEGER *)&CurrentTime))
	{
		io.DeltaTime = (FLOAT)(CurrentTime - g_Time) / g_TicksPerSecond;

		g_Time = CurrentTime;
	}
	else
	{
		return;
	}

	if (GetActiveWindow() == g_d3dPresent.hDeviceWindow && GetCursorPos(&CursorPos) && ScreenToClient(g_d3dPresent.hDeviceWindow, &CursorPos))
	{
		io.MousePos = ImVec2((float)CursorPos.x, (float)CursorPos.y);
	}
	else
	{
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	}
}

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	typedef LRESULT(WINAPI *fn_CallWindowProcA)(WNDPROC, HWND, UINT, WPARAM, LPARAM);

	if (ImGui::GetCurrentContext())
	{
		ImGuiIO& io = ImGui::GetIO();

		switch (uMsg)
		{
		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK: case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK: case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK: case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
		{
			ULONG Button = 0;
			if (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK)
			{
				Button = 0;
			}
			else if (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK)
			{
				Button = 1;
			}
			else if (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK)
			{
				Button = 2;
			}
			else if (uMsg == WM_XBUTTONDOWN || uMsg == WM_XBUTTONDBLCLK)
			{
				Button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4;
			}
			if (!ImGui::IsAnyMouseDown() && !GetCapture())
			{
				SetCapture(hWnd);
			}
			io.MouseDown[Button] = true;
			if (io.WantCaptureMouse)
			{
				return S_OK;
			}
			else
			{
				break;
			}
		}
		case WM_LBUTTONUP: case WM_RBUTTONUP: case WM_MBUTTONUP: case WM_XBUTTONUP:
		{
			ULONG Button = 0;
			if (uMsg == WM_LBUTTONUP)
			{
				Button = 0;
			}
			else if (uMsg == WM_RBUTTONUP)
			{
				Button = 1;
			}
			else if (uMsg == WM_MBUTTONUP)
			{
				Button = 2;
			}
			else if (uMsg == WM_XBUTTONUP)
			{
				Button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4;
			}
			io.MouseDown[Button] = false;
			if (!ImGui::IsAnyMouseDown() && GetCapture() == hWnd)
			{
				ReleaseCapture();
			}
			if (io.WantCaptureMouse)
			{
				return S_OK;
			}
			else
			{
				break;
			}
		}
		case WM_MOUSEWHEEL:
		{
			io.MouseWheel += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
			if (io.WantCaptureMouse)
			{
				return S_OK;
			}
			else
			{
				break;
			}
		}
		case WM_MOUSEHWHEEL:
		{
			io.MouseWheelH += (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
			if (io.WantCaptureMouse)
			{
				return S_OK;
			}
			else
			{
				break;
			}
		}
		case WM_KEYDOWN: case WM_SYSKEYDOWN:
		{
			if (wParam <= 0xFF)
			{
				io.KeysDown[wParam] = true;
			}
			if (wParam == VK_F1)
			{
				g_MenuEnable = !g_MenuEnable;
			}
			if (wParam == VK_HOME)
			{
				g_MenuEnable = !g_MenuEnable;
			}
			break;
		}
		case WM_KEYUP: case WM_SYSKEYUP:
		{
			if (wParam <= 0xFF)
			{
				io.KeysDown[wParam] = false;
			}
			break;
		}
		case WM_CHAR:
		{
			if (wParam > 0 && wParam < 65536)
			{
				io.AddInputCharacterUTF16((unsigned short)wParam);
			}
			break;
		}
		case WM_SIZE:
		{
			ImGui_ImplDX9_Shutdown();

			ImGui_ImplWin32_Shutdown();

			break;
		}
		default:
			break;
		}
	}

	return CallWindowProcA(g_OriginalWndProc, hWnd, uMsg, wParam, lParam);
}