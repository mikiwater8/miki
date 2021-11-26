#pragma once

#define WIN32_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的内容

#include <windows.h>
#include <process.h>
#include <winsock.h>
#include <winreg.h>
#include <assert.h>
#include <psapi.h>
#include <cassert>
#include <time.h>
#include <io.h>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <intrin.h>
#include <tlhelp32.h>
#include <d3d9types.h>

#include "d3d11.h"
#include "d3dx11.h"

#include "sdk.h"
#include "date.h"

#include "imGui\imgui.h"
#include "imGui\D3D11\imgui_impl_dx11.h"
#include "imGui\D3D11\imgui_impl_win32.h"