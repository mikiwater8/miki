#include "stdafx.h"
#define NULL_THREAD        1
#define HIDE_THREAD        2
#define ANTI_DEBUG_THREAD  3

#define MOUSE_BUTTON_1_DOWN    1
#define MOUSE_BUTTON_1_UP      2
#define MOUSE_BUTTON_2_DOWN    4
#define MOUSE_BUTTON_2_UP      8
#define MOUSE_BUTTON_3_DOWN   16
#define MOUSE_BUTTON_3_UP     32
#define MOUSE_BUTTON_4_DOWN   64
#define MOUSE_BUTTON_4_UP    128
#define MOUSE_BUTTON_5_DOWN  256
#define MOUSE_BUTTON_5_UP    512
#define MOUSE_WHEEL         1024

#define KEY_DOWN    0
#define KEY_UP      1

static unsigned long FirstTime = 0;

using namespace std;

typedef void(_fastcall* AttackCache)();
extern AttackCache old_AttackCache;

//extern "C" uintptr_t  WINAPI g_DOGE_back = ((uintptr_t)GetModuleHandleA("GameAssembly.dll") + c_CacheBack);

namespace Bone
{
	enum Bone : INT
	{
		Hips = 0,
		LeftUpperLeg = 1,
		RightUpperLeg = 2,
		LeftLowerLeg = 3,
		RightLowerLeg = 4,
		LeftFoot = 5,
		RightFoot = 6,
		Spine = 7,
		Chest = 8,
		UpperChest = 54,
		Neck = 9,
		Head = 10,
		LeftShoulder = 11,
		RightShoulder = 12,
		LeftUpperArm = 13,
		RightUpperArm = 14,
		LeftLowerArm = 15,
		RightLowerArm = 16,
		LeftHand = 17,
		RightHand = 18,
		LeftToes = 19,
		RightToes = 20,
		LeftEye = 21,
		RightEye = 22,
		Jaw = 23,
		LeftThumbProximal = 24,
		LeftThumbIntermediate = 25,
		LeftThumbDistal = 26,
		LeftIndexProximal = 27,
		LeftIndexIntermediate = 28,
		LeftIndexDistal = 29,
		LeftMiddleProximal = 30,
		LeftMiddleIntermediate = 31,
		LeftMiddleDistal = 32,
		LeftRingProximal = 33,
		LeftRingIntermediate = 34,
		LeftRingDistal = 35,
		LeftLittleProximal = 36,
		LeftLittleIntermediate = 37,
		LeftLittleDistal = 38,
		RightThumbProximal = 39,
		RightThumbIntermediate = 40,
		RightThumbDistal = 41,
		RightIndexProximal = 42,
		RightIndexIntermediate = 43,
		RightIndexDistal = 44,
		RightMiddleProximal = 45,
		RightMiddleIntermediate = 46,
		RightMiddleDistal = 47,
		RightRingProximal = 48,
		RightRingIntermediate = 49,
		RightRingDistal = 50,
		RightLittleProximal = 51,
		RightLittleIntermediate = 52,
		RightLittleDistal = 53,
		LastBone = 55
	};

	list<INT> _上部 = { Neck,Chest };
	list<INT> _右臂 = { Neck, RightShoulder, RightUpperArm, RightUpperArm, RightHand };
	list<INT> _左臂 = { Neck, LeftShoulder, LeftUpperArm, LeftLowerArm, LeftHand };
	list<INT> _脊柱 = { Chest, Hips };
	list<INT> _右腿 = { Hips, RightUpperLeg , RightLowerLeg, RightFoot, RightToes };
	list<INT> _左腿 = { Hips, LeftUpperLeg , LeftLowerLeg, LeftFoot, LeftToes };
	list<list<INT>> BoneList = { _上部, _右臂, _左臂, _脊柱, _右腿, _左腿 };
}

namespace Menu
{
	namespace 菜单设置
	{
		int g_language;
	}

	namespace 全局设置
	{
		bool 战斗模式 = false;

		ImColor 红色 = { 255,0,0,255 };
		ImColor 黄色 = { 255,255,0,180 };
		ImColor 蓝色 = { 0,0,255,200 };
		ImColor 绿色 = { 0,255,0,255 };
		ImColor 艳青 = { 0,255,255,255 };
		ImColor 灰色 = { 155,155,155,220 };
		ImColor 白色 = { 255,255,255,255 };
		ImColor 天蓝 = { 0,136,255,255 };
		ImColor 银白 = { 236,236,236,255 };
		ImColor 黑色 = { 0, 0, 0,255 };
		ImColor 橙黄 = { 255,128,0,255 };
		ImColor 嫩黄 = { 216,216,0,255 };
		ImColor 紫色 = { 144,0,255,255 };
		ImColor 品红 = { 255,0,255,255 };
		ImColor 桃红 = { 255,80,128,255 };
		ImColor 品红2 = { 250,0,250,200 };
		ImColor 绿色2 = { 0,200,0,200 };
		ImColor 天蓝2 = { 0,136,255,200 };
		ImColor 黄色2 = { 250,250,0,200 };

	}

	namespace 玩家透视
	{
		bool 启用透视 = true;
		namespace 透视开关
		{
			bool 显示骨骼 = true;
			bool 显示名字 = false;
			bool 显示血量 = true;
			bool 显示方框 = true;
			bool 显示装备 = true;
			bool 显示射线 = true;
			bool 显示准心 = true;
		}

		namespace 透视颜色
		{
			ImVec4 骨骼颜色 = ImVec4(1.f, 1.f, 1.f, 1.f);
			ImVec4 方框颜色 = ImVec4(1.f, 1.f, 1.f, 1.f);
			ImVec4 名字颜色 = ImVec4(1.f, 1.f, 1.f, 1.f);
			ImVec4 距离颜色 = ImVec4(1.f, 1.f, 1.f, 1.f);
			ImVec4 准心颜色 = ImVec4(0.f, 1.f, 0.f, 1.f);
			ImVec4 射线颜色 = ImVec4(1.f, 1.f, 1.f, 1.f);
		}

		namespace 透视参数
		{
			float 骨骼线条宽度 = 1.5f;
			float 方框线条宽度 = 1.5f;
			float 射线线条宽度 = 1.2f;
			float 准心线条宽度 = 1.2f;
			float 准心尺寸调节 = 3.5f;
			float 透视有效距离 = 500.f;
		}
	}

	namespace 玩家瞄准
	{
		bool 启用瞄准 = true;
		namespace 自瞄开关
		{
			bool 内存自瞄 = false;
			bool 范围开关 = true;
			int    自瞄位置 = Bone::Head;
			int    自瞄热键 = VK_CONTROL;
		}

		namespace 自瞄参数
		{
			FLOAT Value;
			FLOAT RecentValue;
			FLOAT m_AimSpeed = 1.2f;
			FLOAT m_Size = 120.f;
			BOOL m_Lock = FALSE;
			uintptr_t m_TargetObject;
		}
	}

	namespace 物资透视
	{
		namespace 近武
		{
			bool 长剑_白 = false;
			bool 长剑_蓝 = true;
			bool 长剑_紫 = true;
			bool 长剑_金 = true;

			bool 匕首_白 = false;
			bool 匕首_蓝 = true;
			bool 匕首_紫 = true;
			bool 匕首_金 = true;

			bool 长枪_白 = false;
			bool 长枪_蓝 = true;
			bool 长枪_紫 = true;
			bool 长枪_金 = true;

			bool 太刀_白 = false;
			bool 太刀_蓝 = true;
			bool 太刀_紫 = true;
			bool 太刀_金 = true;

			bool 阔刀_白 = false;
			bool 阔刀_蓝 = true;
			bool 阔刀_紫 = true;
			bool 阔刀_金 = true;

			bool 万刃轮_白 = false;
			bool 万刃轮_蓝 = true;
			bool 万刃轮_紫 = true;
			bool 万刃轮_金 = true;
		}

		namespace 远武
		{
			bool 弓箭_白 = false;
			bool 弓箭_蓝 = false;
			bool 弓箭_紫 = true;
			bool 弓箭_金 = true;

			bool 连弩_白 = false;
			bool 连弩_蓝 = false;
			bool 连弩_紫 = true;
			bool 连弩_金 = true;

			bool 火炮_白 = false;
			bool 火炮_蓝 = false;
			bool 火炮_紫 = true;
			bool 火炮_金 = true;

			bool 鸟统_白 = false;
			bool 鸟统_蓝 = false;
			bool 鸟统_紫 = true;
			bool 鸟统_金 = true;

			bool 五眼统_白 = false;
			bool 五眼统_蓝 = false;
			bool 五眼统_紫 = true;
			bool 五眼统_金 = true;

			bool 喷火筒_白 = false;
			bool 喷火筒_蓝 = false;
			bool 喷火筒_紫 = true;
			bool 喷火筒_金 = true;

			bool 壹蜂窝_白 = false;
			bool 壹蜂窝_蓝 = false;
			bool 壹蜂窝_紫 = true;
			bool 壹蜂窝_金 = true;
		}

		namespace 装备
		{
			bool 护甲_白 = false;
			bool 护甲_蓝 = true;
			bool 护甲_紫 = true;
			bool 护甲_金 = true;
		}

		namespace 消耗
		{
			bool 武备匣 = false;
			bool 飞索包 = false;
			bool 小血丸 = false;
			bool 大血丸 = true;
			bool 小甲粉 = false;
			bool 大甲粉 = true;
		}

		namespace 属魂
		{
			bool 攻击_白 = false;
			bool 攻击_蓝 = true;
			bool 攻击_紫 = true;
			bool 攻击_金 = true;

			bool 近抗_白 = false;
			bool 近抗_蓝 = true;
			bool 近抗_紫 = true;
			bool 近抗_金 = true;

			bool 远抗_白 = false;
			bool 远抗_蓝 = true;
			bool 远抗_紫 = true;
			bool 远抗_金 = true;

			bool 体力_白 = false;
			bool 体力_蓝 = true;
			bool 体力_紫 = true;
			bool 体力_金 = true;
		}

		namespace 特魂
		{
			bool 妙手 = true;
			bool 巧匠 = true;
			bool 凌波 = true;
			bool 完璧 = true;

			bool 光佑 = true;
			bool 猫足 = true;
			bool 财迷 = true;
			bool 安神 = true;

			bool 毕工淌 = true;
			bool 吐纳术 = true;
			bool 虚影步 = true;
			bool 地堂脚 = true;

			bool 天赐飞索 = true;
			bool 天赐武备 = true;
			bool 燃魂一线 = true;
			bool 抽芯补天 = true;
		}
		namespace 近魂
		{
			bool 噬魂斩 = true;
			bool 青鬼 = true;
			bool 归元 = true;
			bool 太刀 = true;
			bool 烈火斩 = true;
			bool 破风 = true;
			bool 裂空 = true;
			bool 阔刀 = true;
			bool 凤凰羽 = true;
			bool 蓝月 = true;
			bool 伏天 = true;
			bool 长剑 = true;
			bool 空弹 = true;
		}
		namespace 远魂
		{
			bool 散射 = true;
			bool 羚羊 = true;
			bool 爆裂 = true;
			bool 速射 = true;
			bool 精准 = true;
			bool 毒箭 = true;
			bool 连珠炮 = true;
			bool 反弹 = true;
			bool 集束 = true;
			bool 落金屋 = true;
			bool 甲破 = true;
		}
		namespace 其他
		{
			bool 尸盒 = false;
			bool 刺梨 = true;
			bool 沙叻 = true;
			bool 蒲公英 = true;
			bool 萤火虫 = true;
			bool 武器扩容 = true;
			bool 魂玉扩容 = true;
			bool 背包扩容 = true;
		}
	}

	namespace 预警设置
	{
		namespace 预警开关
		{
			bool 盲区预警 = true;
		}

		namespace 预警颜色
		{
			ImVec4 盲区近距预警颜色 = ImVec4(1.f, 0.f, 0.f, 1.f);
			ImVec4 盲区中距预警颜色 = ImVec4(1.f, 1.f, 0.f, 1.f);
			ImVec4 盲区远距预警颜色 = ImVec4(1.f, 1.f, 1.f, 1.f);
		}

		namespace 预警参数
		{
			float 最近距离 = 0.f;
			int 盲区敌人数量 = 0;
		}
	}

	namespace 功能设置
	{
		namespace 功能开关
		{
			bool 强制震刀 = true;
			bool 模拟震刀 = false;
			bool 反震升龙 = true;
			//bool 锁龙王破 = false;
			//bool 快速蓄力 = false;
			bool 自动连招 = false;
			bool 无限精力 = false;

			bool 凌波微步 = false;
			bool 逆天改命 = false;
			bool 飞龙缠身 = false;
		}

		namespace 功能参数
		{
			int 强制类型 = VK_SPACE;
			FLOAT 跳振延迟 = 1.F;
			FLOAT 蹲振延迟 = 2.F;
			FLOAT 震刀延迟 = 6.F;
		}
	}
}

FLOAT TakeCollimatedDistance(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2)
{
	return sqrtf((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
}

VOID DbgPrint(LPCSTR szFormat, ...)
{
	static bool bDbgPrint = false;
	if (!bDbgPrint)
	{
		bDbgPrint = AllocConsole();
		if (bDbgPrint)
		{
			freopen_s((_iobuf**)__acrt_iob_func(0), "conin$", "r", (_iobuf*)__acrt_iob_func(0));
			freopen_s((_iobuf**)__acrt_iob_func(1), "conout$", "w", (_iobuf*)__acrt_iob_func(1));
			freopen_s((_iobuf**)__acrt_iob_func(2), "conout$", "w", (_iobuf*)__acrt_iob_func(2));
		}
	}
	char szBuffer[1024] = { 0 };
	va_list pArgList;
	va_start(pArgList, szFormat);
	_vsnprintf_s(szBuffer, sizeof(szBuffer) / sizeof(char), szFormat, pArgList);
	va_end(pArgList);
	char szOutBuffer[1024] = { 0 };
	sprintf_s(szOutBuffer, "[+] %s \n", szBuffer);
	printf(szOutBuffer);
}

DOUBLE Radians(DOUBLE Angle)
{
	return Angle * 0.01745329251994;
}

BOOL IsValues(FLOAT minhp, FLOAT maxhp, FLOAT* Save)
{
	if (maxhp <= 0.f)return FALSE;
	*Save = minhp / maxhp * 100;
	return TRUE;
}

Vector3 GetMidPoint(Vector3 V1, Vector3 V2)
{
	return Vector3((V1.x + V2.x) / 2, (V1.y + V2.y) / 2, (V1.z + V2.z) / 2);
}

namespace Draw
{
	ULONG64 OldPresent = NULL;
	char* UnicodeToAnsi(char* Unicode, UINT CP)
	{
		if (CP == 0)
			CP = 0;
		int i = WideCharToMultiByte(0, 0, (LPCWSTR)Unicode, -1, NULL, 0, 0, 0);
		char* ansi;
		ansi = new char[i * 2];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)Unicode, -1, ansi, i * 2, 0, 0);
		//std::strcpy(Unicode, ansi);
		return ansi;
	}

	string AnsiToUTF8(CONST string& str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);
		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		string retStr(pBuf);
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}

	wstring AsciiToUnicode(CONST string& str) {
		// 预算-缓冲区中宽字节的长度    
		int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
		// 给指向缓冲区的指针变量分配内存    
		wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
		// 开始向缓冲区转换字节    
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
		wstring ret_str = pUnicode;
		free(pUnicode);
		return ret_str;
	}

	string UnicodeToAscii(CONST wstring& wstr) {
		// 预算-缓冲区中多字节的长度    
		int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		// 给指向缓冲区的指针变量分配内存    
		char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
		// 开始向缓冲区转换字节    
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
		string ret_str = pAssii;
		free(pAssii);
		return ret_str;
	}

	string UnicodeToUtf8(CONST wstring& wstr) {
		// 预算-缓冲区中多字节的长度    
		int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		// 给指向缓冲区的指针变量分配内存    
		char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
		// 开始向缓冲区转换字节    
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
		string ret_str = pAssii;
		free(pAssii);
		return ret_str;
	}

	wstring Utf8ToUnicode(CONST string& str) {
		// 预算-缓冲区中宽字节的长度    
		int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		// 给指向缓冲区的指针变量分配内存    
		wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
		// 开始向缓冲区转换字节    
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
		wstring ret_str = pUnicode;
		free(pUnicode);
		return ret_str;
	}

	string Utf8ToAscii(CONST string& str) {
		return UnicodeToAscii(Utf8ToUnicode(str));
	}

	string AsciiToUtf8(CONST string& str) {
		return UnicodeToUtf8(AsciiToUnicode(str));
	}

	VOID Text(FLOAT X, FLOAT Y, ImColor Color, FLOAT Size, CONST CHAR* Str, ...)
	{
		std::string utf_8_1 = std::string(Str);
		std::string utf_8_2 = AnsiToUTF8(utf_8_1);
		std::stringstream stream(utf_8_2.c_str());
		string line;
		float yy = 0.0f;
		int i = 0;
		while (std::getline(stream, line))
		{

			ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(Size, FLT_MAX, 0.0f, line.c_str());
			ImGui::GetOverlayDrawList()->AddText(ImVec2((X - textSize.x / 2.0f), (Y + textSize.y * i)), Size, ImGui::ColorConvertFloat4ToU32(Color), line.c_str());
			yy = Y + textSize.y * (i + 1);
			i++;
		}
	}

	VOID TextEx(FLOAT X, FLOAT Y, ImColor Color, FLOAT Size, CONST CHAR* Str, ...)
	{
		CHAR Buffer[1024] = { 0 };
		va_list va_alist;
		va_start(va_alist, Str);
		vsprintf_s(Buffer, Str, va_alist);
		va_end(va_alist);
		ImGui::GetOverlayDrawList()->AddTextEx(ImVec2(X, Y), Size, ImGui::ColorConvertFloat4ToU32(Color), Buffer);
	}

	VOID DrawStrokeText(FLOAT x, FLOAT y, ImColor color, CONST std::string& text, FLOAT thickness)
	{
		std::string utf_8_1 = std::string(text);
		std::string utf_8_2 = AnsiToUTF8(utf_8_1);

		std::stringstream stream(utf_8_2.c_str());
		string line;

		float yy = 0.0f;
		int i = 0;
		while (std::getline(stream, line))
		{
			ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(thickness, FLT_MAX, 0.0f, line.c_str());
			ImGui::GetOverlayDrawList()->AddTextEx(ImVec2((x - textSize.x / 2.0f) + 1, (y + textSize.y * i) + 1), thickness, ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), line.c_str());
			ImGui::GetOverlayDrawList()->AddTextEx(ImVec2((x - textSize.x / 2.0f) - 1, (y + textSize.y * i) - 1), thickness, ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), line.c_str());
			ImGui::GetOverlayDrawList()->AddTextEx(ImVec2((x - textSize.x / 2.0f) + 1, (y + textSize.y * i) - 1), thickness, ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), line.c_str());
			ImGui::GetOverlayDrawList()->AddTextEx(ImVec2((x - textSize.x / 2.0f) - 1, (y + textSize.y * i) + 1), thickness, ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), line.c_str());
			ImGui::GetOverlayDrawList()->AddTextEx(ImVec2((x - textSize.x / 2.0f), (y + textSize.y * i)), thickness, ImGui::ColorConvertFloat4ToU32(color), line.c_str());
			yy = y + textSize.y * (i + 1);
			i++;
		}
	}

	VOID CircleFilled(FLOAT X, FLOAT Y, FLOAT Radius, ImColor Color, INT Segments)
	{
		ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(X, Y), Radius, ImGui::ColorConvertFloat4ToU32(Color), Segments);
	}


	VOID DrawCircle(FLOAT x, FLOAT y, FLOAT radius, ImColor color, INT segments, FLOAT thickness)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(color), segments, thickness);
	}

	VOID Rect(FLOAT X, FLOAT Y, FLOAT W, FLOAT H, ImColor Color, FLOAT Width)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(Color), 0, 0, Width);
	}

	VOID FilledRect(FLOAT X, FLOAT Y, FLOAT W, FLOAT H, ImColor Color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X + 1, Y + 1), ImVec2(((X + W) - 1), ((Y + H) - 1)), Color);
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X, Y), ImVec2(X + W, Y + H), Color);
		//ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), 0, 0);
	}

	VOID Line(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, ImColor Color, FLOAT Width)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X1, Y1), ImVec2(X2, Y2), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);
	}
}

namespace Module
{
	uintptr_t GameBase = 0;
	uintptr_t UnityPlayer = 0;
	uintptr_t GameAssembly = 0;
	uintptr_t GameOverlayRenderer = 0;
}

namespace Memory
{
	template<typename T> T Read(uintptr_t _Dst)
	{
		T Ele;

		if (IsBadHugeReadPtr((PVOID)_Dst, sizeof(T)) == 0)
			Ele = *reinterpret_cast<T*>(_Dst);

		return Ele;
	}

	template<typename T> VOID Write(uintptr_t _Dst, T _Src)
	{
		if (IsBadHugeWritePtr((PVOID)_Dst, sizeof(T)) == 0)
			*reinterpret_cast<T*>(_Dst) = _Src;
	}

	template< typename ReturnType = void, typename... Args >ReturnType CALL(uintptr_t ufn, Args... Arguments)
	{
		return reinterpret_cast<ReturnType(*)(Args...)>(ufn)(Arguments...);
	}

	BOOL ValidPtr(uintptr_t Ptr)
	{
		return (BOOL)(Ptr < 0xFFFF || Ptr > 0x7FFFFFFFFFFF || Ptr % sizeof(uintptr_t));
	}

	VOID JMP(uintptr_t HookAddress, uintptr_t JumpToAddress)
	{
		unsigned char ShellCode[] = { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

		*(uintptr_t*)(ShellCode + 6) = JumpToAddress;

		for (size_t i = 0; i < sizeof(ShellCode); i++)
		{
			((BYTE*)HookAddress)[i] = ShellCode[i];
		}
	}

	VOID RtlCopyMemoryEx(PBYTE _Dst, PBYTE _Src, SIZE_T _Size)
	{
		for (size_t i = 0; i < _Size; i++)
		{
			_Dst[i] = _Src[i];
		}
	}

	VOID RtlZeroMemoryEx(PBYTE _Dst, SIZE_T _Size)
	{
		for (size_t i = 0; i < _Size; i++)
		{
			_Dst[i] = (BYTE)NULL;
		}
	}

	VOID RtlFillMemoryEx(PBYTE _Dst, BYTE _Src, SIZE_T _Size)
	{
		for (size_t i = 0; i < _Size; i++)
		{
			_Dst[i] = (BYTE)_Src;
		}
	}

	BOOL Read(uintptr_t addr, uintptr_t buff, uintptr_t bufSize)
	{
		if (IsBadHugeReadPtr((PVOID)addr, bufSize) == 0)
		{
			RtlCopyMemoryEx((PBYTE)buff, (PBYTE)addr, bufSize);
			return true;
		}
		else
		{
			return false;
		}
	}

	BOOL Compare(CONST BYTE* pData, CONST BYTE* bMask, CONST CHAR* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)
				return FALSE;
		return (*szMask) == NULL;
	}

	uintptr_t FindPatternForMemory(uintptr_t StartAddress, uintptr_t EndAddress, BYTE* bMask, std::string szMask)
	{
		ULONG ImageLen = EndAddress - StartAddress;

		INT MaskLen = szMask.length();

		for (ULONG i = 0; i < ImageLen - MaskLen; i++)
		{
			if (IsBadHugeReadPtr((PVOID)(StartAddress + i), 1) == 0)
			{
				if (Compare((BYTE*)(StartAddress + i), bMask, szMask.c_str()))
				{
					return (uintptr_t)(StartAddress + i);
				}
			}
		}

		return 0;
	}

	uintptr_t FindPatternForModule(uintptr_t dwModule, BYTE* bMask, std::string szMask)
	{
		PIMAGE_DOS_HEADER pImageDos = (PIMAGE_DOS_HEADER)dwModule;

		PIMAGE_NT_HEADERS32 pImageNt = (PIMAGE_NT_HEADERS32)(dwModule + pImageDos->e_lfanew);

		ULONG ImageLen = pImageNt->OptionalHeader.SizeOfImage;

		INT MaskLen = szMask.length();

		for (ULONG i = 0; i < ImageLen - MaskLen; i++)
		{
			if (IsBadHugeReadPtr((PVOID)(dwModule + i), 1) == 0)
			{
				if (Compare((BYTE*)(dwModule + i), bMask, szMask.c_str()))
				{
					return (uintptr_t)(dwModule + i);
				}
			}
		}

		return 0;
	}

	namespace _SpoofCallInternal {

		extern "C" PVOID _spoofer_stub();

		template <typename Ret, typename... Args>
		inline Ret Wrapper(PVOID shell, Args... args) {
			auto fn = (Ret(*)(Args...))(shell);
			return fn(args...);
		}

		template <std::size_t Argc, typename>
		struct Remapper {
			template<typename Ret, typename First, typename Second, typename Third, typename Fourth, typename... Pack>
			static Ret Call(PVOID shell, PVOID shell_param, First first, Second second, Third third, Fourth fourth, Pack... pack) {
				return Wrapper<Ret, First, Second, Third, Fourth, PVOID, PVOID, Pack...>(shell, first, second, third, fourth, shell_param, nullptr, pack...);
			}
		};

		template <std::size_t Argc>
		struct Remapper<Argc, std::enable_if_t<Argc <= 4>> {
			template<typename Ret, typename First = PVOID, typename Second = PVOID, typename Third = PVOID, typename Fourth = PVOID>
			static Ret Call(PVOID shell, PVOID shell_param, First first = First{}, Second second = Second{}, Third third = Third{}, Fourth fourth = Fourth{}) {
				return Wrapper<Ret, First, Second, Third, Fourth, PVOID, PVOID>(shell, first, second, third, fourth, shell_param, nullptr);
			}
		};
	}

	template <typename Ret, typename... Args>
	Ret SpoofCall(Ret(*fn)(Args...), Args... args) {
		static PVOID trampoline = nullptr;
		if (!trampoline) {

			trampoline = (PVOID)Memory::FindPatternForModule(Module::GameAssembly, (PBYTE)"\xFF\x23", "xx");
			if (!trampoline) {
				ExitProcess(0);
			}
		}
		struct {
			PVOID Trampoline;
			PVOID Function;
			PVOID Reg;
		} params = {
			trampoline,
			reinterpret_cast<void*>(fn),
		};

		return _SpoofCallInternal::Remapper<sizeof...(Args), void>::template Call<Ret, Args...>(&_SpoofCallInternal::_spoofer_stub, &params, args...);
	}
}

namespace ZhenDao
{
	BOOL Thread = FALSE;
	WNDPROC GameWndProc = NULL;

	namespace Best
	{
		ULONG32 BestSleepTime = NULL;
		ULONG64 BestPlayerPtr = NULL;
		FLOAT BestPlayerDistance = 0.f;
	}

	namespace Vector
	{
		vector<ULONG> SleepList;
		vector<FLOAT> DistanceList;
		vector<ULONG_PTR> PlayerPtrList;
	}
}

namespace BaoMing
{
	ULONG64 TickCount = NULL;

	Vector3 SavePosition[50];
}

namespace XiDiRen
{
	namespace Vector
	{
		vector<ULONG> HealthList;
		vector<Vector3> PositionList;
	}
}

namespace GameData
{
	namespace Base
	{
		ULONG64 UWorld = 0;
		ULONG64 EntityManager = 0;
		ULONG64 Client = 0;
		ULONG64 Matrix = 0;
	}

	namespace ActorList
	{
		ULONG64 ActorBase = 0;
		ULONG64 ActorList = 0;
		ULONG64 ActorArray = 0;
		ULONG64 ActorConut = 0;
		ULONG64 ActorInGame = 0;
	}

	namespace OtherList
	{
		ULONG64 OtherBase = 0;
		ULONG64 OtherList = 0;
		ULONG64 OtherArray = 0;
		ULONG64 OtherConut = 0;
	}

	namespace LocalPlayer
	{
		ULONG64 Ptr = 0;
		ULONG64 Team = 0;
		ULONG64 State = 0;
		ULONG64 ActorKit = 0;
		ULONG64 WeaponId = 0;
		ULONG64 BlueSkills = 0;
		FWeaponData WeaponData = FWeaponData{ 0, 0, 0 };
		FHealthData HealthData = FHealthData{ 0, 0, 0, 0, 0 };
		Vector3 Position = Vector3{ 0.f, 0.f, 0.f };
		FRotator Yaw = FRotator{ 0.f, 0.f, 0.f };
	}

	namespace DrawOverlay
	{
		vector<Vector2> ItemList;
	}
}

namespace GSInject
{
	BOOL SendDrvMsg(DWORD Code, PVOID Data, ULONG DataSize)
	{
		return RegSetValueExA(HKEY_CURRENT_USER, NULL, NULL, Code, (CONST BYTE*)Data, DataSize) == 998;
	}

	BOOL DeleteInject()
	{
		return SendDrvMsg(0x1001, NULL, NULL);
	}

	namespace SSDT
	{
		BOOL CreateThreadEx(ULONGLONG StratAddress, ULONG Flags, BOOL BypassKernelThreadNotify)
		{
			/*
				NULL_THREAD        1
				HIDE_THREAD        2
				ANTI_DEBUG_THREAD  3
			*/

			static struct
			{
				ULONGLONG StratAddress;
				ULONGLONG ThreadType;
				ULONGLONG BypassNotify;
			} Structs;

			RtlZeroMemory(&Structs, sizeof(Structs));

			Structs.StratAddress = StratAddress;

			Structs.ThreadType = Flags;

			Structs.BypassNotify = BypassKernelThreadNotify;

			return SendDrvMsg(0x1002, &Structs, sizeof(Structs));
		}

		BOOL VirtualProtect(ULONGLONG MemoryAddress, ULONGLONG MemorySize, ULONG NewProtect)
		{
			static struct
			{
				ULONGLONG MemoryAddress;
				ULONGLONG MemorySize;
				ULONGLONG NewProtect;
			} Structs;

			RtlZeroMemory(&Structs, sizeof(Structs));

			Structs.MemoryAddress = MemoryAddress;

			Structs.MemorySize = MemorySize;

			Structs.NewProtect = NewProtect;

			return SendDrvMsg(0x1003, &Structs, sizeof(Structs));
		}

		BOOL VirtualQuery(ULONGLONG MemoryAddress, PVOID BufferAddress, ULONGLONG BufferSize)
		{
			static struct
			{
				ULONGLONG MemoryAddress;
				ULONGLONG BufferAddress;
				ULONGLONG BufferSize;
			} Structs;

			RtlZeroMemory(&Structs, sizeof(Structs));

			Structs.MemoryAddress = MemoryAddress;

			Structs.BufferAddress = (ULONGLONG)BufferAddress;

			Structs.BufferSize = BufferSize;

			return SendDrvMsg(0x1004, &Structs, sizeof(Structs));
		}

		ULONGLONG VirtualAllocate(ULONGLONG DesiredAddress, ULONGLONG RegionSize, ULONGLONG HideMemory)
		{
			static struct
			{
				ULONGLONG DesiredAddress;
				ULONGLONG RegionSize;
				ULONGLONG HideMemory;
				ULONGLONG BufferAddress;
			} Structs;

			RtlZeroMemory(&Structs, sizeof(Structs));

			Structs.DesiredAddress = DesiredAddress;

			Structs.RegionSize = RegionSize;

			Structs.HideMemory = HideMemory;

			Structs.BufferAddress = (ULONGLONG)&Structs.BufferAddress;

			return SendDrvMsg(0x1005, &Structs, sizeof(Structs)) ? Structs.BufferAddress : NULL;
		}
	}

	namespace Mouse
	{
		BOOL SimulatedMove(ULONG X, ULONG Y, ULONG Flags)
		{
			static struct
			{
				USHORT UnitId;
				USHORT Flags;
				union {
					ULONG Buttons;
					struct {
						USHORT  ButtonFlags;
						USHORT  ButtonData;
					};
				};
				ULONG RawButtons;
				LONG LastX;
				LONG LastY;
				ULONG ExtraInformation;
			} Structs;

			RtlZeroMemory(&Structs, sizeof(Structs));

			if (Flags == MOUSE_MOVE_RELATIVE)
			{
				Structs.LastX = X;

				Structs.LastY = Y;
			}

			if (Flags == MOUSE_MOVE_ABSOLUTE)
			{
				Structs.LastX = X * 65535 / GetSystemMetrics(SM_CXSCREEN);

				Structs.LastY = Y * 65535 / GetSystemMetrics(SM_CYSCREEN);
			}

			return SendDrvMsg(0x1006, &Structs, sizeof(Structs));
		}

		BOOL SimulatedButton(ULONG ButtonFlags)
		{
			/*
				MOUSE_BUTTON_1_DOWN    1
				MOUSE_BUTTON_1_UP      2
				MOUSE_BUTTON_2_DOWN    4
				MOUSE_BUTTON_2_UP      8
				MOUSE_BUTTON_3_DOWN   16
				MOUSE_BUTTON_3_UP     32
				MOUSE_BUTTON_4_DOWN   64
				MOUSE_BUTTON_4_UP    128
				MOUSE_BUTTON_5_DOWN  256
				MOUSE_BUTTON_5_UP    512
				MOUSE_WHEEL         1024
			*/

			static struct
			{
				USHORT UnitId;
				USHORT Flags;
				union {
					ULONG Buttons;
					struct {
						USHORT  ButtonFlags;
						USHORT  ButtonData;
					};
				};
				ULONG RawButtons;
				LONG LastX;
				LONG LastY;
				ULONG ExtraInformation;
			} Structs;

			RtlZeroMemory(&Structs, sizeof(Structs));

			Structs.ButtonFlags = (USHORT)ButtonFlags;

			return SendDrvMsg(0x1006, &Structs, sizeof(Structs));
		}
	}

	namespace Keyboard
	{
		BOOL SimulatedInput(ULONG Key, ULONG Flags)
		{
			/*
				KEY_DOWN    0
				KEY_UP      1
			*/

			static struct
			{
				USHORT UnitId;
				USHORT MakeCode;
				USHORT Flags;
				USHORT Reserved;
				ULONG ExtraInformation;
			} Structs;

			RtlZeroMemory(&Structs, sizeof(Structs));

			Structs.Flags = (USHORT)Flags;

			Structs.MakeCode = (USHORT)MapVirtualKeyA(Key, 0);;

			return SendDrvMsg(0x1007, &Structs, sizeof(Structs));
		}
	}
}

namespace UnityEngine
{
	Vector3 TransformToWorld(ULONG64 EntityPtr)
	{
		Vector3 WorldPos = { 0.f, 0.f, 0.f };

		((VOID(__fastcall*)(Vector3&, ULONG64))(Module::GameAssembly + UnityEngine_TransformToWorld_1))(WorldPos, EntityPtr);

		return WorldPos;
	}

	ULONG64 GetBoneTransform(ULONG64 ComponentPtr, ULONG Index)
	{
		return ((ULONG64(__fastcall*)(ULONG64, ULONG64, ULONG64, ULONG64, ULONG64, ULONG64, ULONG))(Module::GameAssembly + UnityEngine_GetBoneTransform_1))(ComponentPtr, Index, NULL, NULL, NULL, NULL, NULL);
	}

	ULONG64 GetOtherTransform(ULONG64 EntityPtr)
	{
		return ((ULONG64(__fastcall*)(ULONG64))(Module::GameAssembly + UnityEngine_GetOtherTransform_1))(EntityPtr);
	}
}

void MouseAimBot(Vector3 Output, bool Smooth)
{
	float TargetX, TargetY, SightX, SightY;
	TargetX = 0;
	TargetY = 0;
	SightX = g_d3dViewPort.Width * 0.5f;
	SightY = g_d3dViewPort.Height * 0.5f;
	if (Output.x != 0)
	{
		if (Output.x > SightX)
		{
			TargetX = -(SightX - Output.x);
			TargetX = TargetX / Menu::玩家瞄准::自瞄参数::m_AimSpeed;
			if (TargetX + SightX > SightX * 2)
			{
				TargetX = 0;
			}
		}
		if (Output.x < SightX)
		{
			TargetX = Output.x - SightX;
			TargetX = TargetX / Menu::玩家瞄准::自瞄参数::m_AimSpeed;
			if (TargetX + SightX < 0)
			{
				TargetX = 0;
			}
		}
	}
	if (Output.y != 0)
	{
		if (Output.y > SightY)
		{
			TargetY = -(SightY - Output.y);
			TargetY = TargetY / Menu::玩家瞄准::自瞄参数::m_AimSpeed;
			if (TargetY + SightY > SightY * 2)
			{
				TargetY = 0;
			}
		}
		if (Output.y < SightY)
		{
			TargetY = Output.y - SightY;
			TargetY = TargetY / Menu::玩家瞄准::自瞄参数::m_AimSpeed;
			if (TargetY + SightY < 0)
			{
				TargetY = 0;
			}
		}
	}
	if (Smooth == false)
	{
		GSInject::Mouse::SimulatedMove(TargetX, TargetY, NULL);
		//mouse_move( TargetX, TargetY);
		//AimBot_API(TargetX, TargetY);
		return;
	}
	TargetX = TargetX / 3;
	TargetY = TargetY / 3;
	if (fabs(TargetX) < 1)
	{
		if (TargetX > 0)
			TargetX = 0.9;
		if (TargetX < 0)
			TargetX = -0.9;
	}
	if (fabs(TargetY) < 1)
	{
		if (TargetY > 0)
			TargetY = 0.9;
		if (TargetY < 0)
			TargetY = -0.9;
	}
	GSInject::Mouse::SimulatedMove(TargetX, TargetY, NULL);
	//mouse_move( TargetX, TargetY);
	//AimBot_API(TargetX, TargetY); 
	//GSInject::Mouse::SimulatedMove(TargetX, TargetY, NULL);
}

void Menustyler()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(16, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildRounding = 0.0f;
	style.FramePadding = ImVec2(4, 3);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(4, 3);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 8.f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 1.0f;
	style.GrabRounding = 0.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	//style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;
	style.FrameBorderSize = 1.0f;
}

void Menucolor()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.92f, 0.18f, 0.29f, 0.37f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.92f, 0.18f, 0.29f, 0.75f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.92f, 0.18f, 0.29f, 0.63f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
}

void Setlanguage()
{
	if (ImGui::CollapsingHeader(Menu::菜单设置::g_language == 0 ? (u8"菜单") : ("Menu")))
	{
		ImGui::Indent();
		ImGui::BulletText(Menu::菜单设置::g_language == 0 ? u8"当前帧数 %1.f FPS 每秒" : "Current frames %1.f FPS m/s", ImGui::GetIO().Framerate);
		ImGui::Text((u8"Language")); ImGui::SameLine();
		ImGui::Combo("", &Menu::菜单设置::g_language, (u8"中文\0English\0"));
		ImGui::Text("\n");
		ImGui::Unindent();
	}
}

void SetESPlayer()
{
	if (ImGui::CollapsingHeader(((Menu::菜单设置::g_language == 0) ? (u8"透视") : ("Visus"))))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader(((Menu::菜单设置::g_language == 0) ? (u8"玩家") : ("Player"))))
		{
			ImGui::Indent();
			ImGui::MenuItem(Menu::菜单设置::g_language == 0 ? (u8"视觉启用") : ("SEP Enable"), "", &Menu::玩家透视::启用透视);
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"显示骨骼") : ("Skeleton"), &Menu::玩家透视::透视开关::显示骨骼); ImGui::SameLine(180.f);
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"显示名字") : ("Name"), &Menu::玩家透视::透视开关::显示名字);		ImGui::SameLine(280.f);
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"显示血量") : ("Health"), &Menu::玩家透视::透视开关::显示血量); ImGui::SameLine(380.f);
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"显示方框") : ("Box"), &Menu::玩家透视::透视开关::显示方框);

			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"预警显示") : ("Blind spots"), &Menu::预警设置::预警开关::盲区预警); ImGui::SameLine(180.f);
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"显示射线") : ("RayLine"), &Menu::玩家透视::透视开关::显示射线); ImGui::SameLine(280.f);
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"显示装备") : ("Equipment"), &Menu::玩家透视::透视开关::显示装备); ImGui::SameLine(380.f);
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"显示准心") : ("Quasar"), &Menu::玩家透视::透视开关::显示准心);


			ImGui::Text("\n");
			ImGui::Unindent();

		}

		if (ImGui::CollapsingHeader(Menu::菜单设置::g_language == 0 ? u8"物品##2" : "Items"))
		{
			ImGui::Indent();
			if (ImGui::TreeNode(u8"近武##2_1"))
			{
				ImGui::Checkbox(u8"长剑(白)　　##2_1_1", &Menu::物资透视::近武::长剑_白); ImGui::SameLine();
				ImGui::Checkbox(u8"长剑(蓝)　　##2_1_2", &Menu::物资透视::近武::长剑_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"长剑(紫)　　##2_1_3", &Menu::物资透视::近武::长剑_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"长剑(金)　　##2_1_4", &Menu::物资透视::近武::长剑_金);

				ImGui::Checkbox(u8"匕首(白)　　##2_1_5", &Menu::物资透视::近武::匕首_白); ImGui::SameLine();
				ImGui::Checkbox(u8"匕首(蓝)　　##2_1_6", &Menu::物资透视::近武::匕首_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"匕首(紫)　　##2_1_7", &Menu::物资透视::近武::匕首_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"匕首(金)　　##2_1_8", &Menu::物资透视::近武::匕首_金);

				ImGui::Checkbox(u8"长枪(白)　　##2_1_9", &Menu::物资透视::近武::长枪_白); ImGui::SameLine();
				ImGui::Checkbox(u8"长枪(蓝)　　##2_1_10", &Menu::物资透视::近武::长枪_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"长枪(紫)　　##2_1_11", &Menu::物资透视::近武::长枪_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"长枪(金)　　##2_1_12", &Menu::物资透视::近武::长枪_金);

				ImGui::Checkbox(u8"太刀(白)　　##2_1_13", &Menu::物资透视::近武::太刀_白); ImGui::SameLine();
				ImGui::Checkbox(u8"太刀(蓝)　　##2_1_14", &Menu::物资透视::近武::太刀_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"太刀(紫)　　##2_1_15", &Menu::物资透视::近武::太刀_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"太刀(金)　　##2_1_16", &Menu::物资透视::近武::太刀_金);

				ImGui::Checkbox(u8"阔刀(白)　　##2_1_17", &Menu::物资透视::近武::阔刀_白); ImGui::SameLine();
				ImGui::Checkbox(u8"阔刀(蓝)　　##2_1_18", &Menu::物资透视::近武::阔刀_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"阔刀(紫)　　##2_1_19", &Menu::物资透视::近武::阔刀_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"阔刀(金)　　##2_1_20", &Menu::物资透视::近武::阔刀_金);

				ImGui::Checkbox(u8"万刃轮(白)　##2_1_21", &Menu::物资透视::近武::万刃轮_白); ImGui::SameLine();
				ImGui::Checkbox(u8"万刃轮(蓝)　##2_1_22", &Menu::物资透视::近武::万刃轮_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"万刃轮(紫)　##2_1_23", &Menu::物资透视::近武::万刃轮_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"万刃轮(金)　##2_1_24", &Menu::物资透视::近武::万刃轮_金);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"远武##2_2"))
			{
				ImGui::Checkbox(u8"弓箭(白)　　##2_2_1", &Menu::物资透视::远武::弓箭_白); ImGui::SameLine();
				ImGui::Checkbox(u8"弓箭(蓝)　　##2_2_2", &Menu::物资透视::远武::弓箭_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"弓箭(紫)　　##2_2_3", &Menu::物资透视::远武::弓箭_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"弓箭(金)　　##2_2_4", &Menu::物资透视::远武::弓箭_金);

				ImGui::Checkbox(u8"连弩(白)　　##2_2_5", &Menu::物资透视::远武::连弩_白); ImGui::SameLine();
				ImGui::Checkbox(u8"连弩(蓝)　　##2_2_6", &Menu::物资透视::远武::连弩_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"连弩(紫)　　##2_2_7", &Menu::物资透视::远武::连弩_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"连弩(金)　　##2_2_8", &Menu::物资透视::远武::连弩_金);

				ImGui::Checkbox(u8"火炮(白)　　##2_2_9", &Menu::物资透视::远武::火炮_白); ImGui::SameLine();
				ImGui::Checkbox(u8"火炮(蓝)　　##2_2_10", &Menu::物资透视::远武::火炮_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"火炮(紫)　　##2_2_11", &Menu::物资透视::远武::火炮_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"火炮(金)　　##2_2_12", &Menu::物资透视::远武::火炮_金);

				ImGui::Checkbox(u8"鸟统(白)　　##2_2_13", &Menu::物资透视::远武::鸟统_白); ImGui::SameLine();
				ImGui::Checkbox(u8"鸟统(蓝)　　##2_2_14", &Menu::物资透视::远武::鸟统_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"鸟统(紫)　　##2_2_15", &Menu::物资透视::远武::鸟统_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"鸟统(金)　　##2_2_16", &Menu::物资透视::远武::鸟统_金);

				ImGui::Checkbox(u8"五眼统(白)　##2_2_17", &Menu::物资透视::远武::五眼统_白); ImGui::SameLine();
				ImGui::Checkbox(u8"五眼统(蓝)　##2_2_18", &Menu::物资透视::远武::五眼统_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"五眼统(紫)　##2_2_19", &Menu::物资透视::远武::五眼统_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"五眼统(金)　##2_2_20", &Menu::物资透视::远武::五眼统_金);

				ImGui::Checkbox(u8"喷火筒(白)　##2_2_21", &Menu::物资透视::远武::喷火筒_白); ImGui::SameLine();
				ImGui::Checkbox(u8"喷火筒(蓝)　##2_2_22", &Menu::物资透视::远武::喷火筒_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"喷火筒(紫)　##2_2_23", &Menu::物资透视::远武::喷火筒_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"喷火筒(金)　##2_2_24", &Menu::物资透视::远武::喷火筒_金);

				ImGui::Checkbox(u8"壹蜂窝(白)　##2_2_25", &Menu::物资透视::远武::壹蜂窝_白); ImGui::SameLine();
				ImGui::Checkbox(u8"壹蜂窝(蓝)　##2_2_26", &Menu::物资透视::远武::壹蜂窝_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"壹蜂窝(紫)　##2_2_27", &Menu::物资透视::远武::壹蜂窝_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"壹蜂窝(金)　##2_2_28", &Menu::物资透视::远武::壹蜂窝_金);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"装备##2_3"))
			{
				ImGui::Checkbox(u8"护甲(白)　　##2_3_1", &Menu::物资透视::装备::护甲_白); ImGui::SameLine();
				ImGui::Checkbox(u8"护甲(蓝)　　##2_3_2", &Menu::物资透视::装备::护甲_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"护甲(紫)　　##2_3_3", &Menu::物资透视::装备::护甲_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"护甲(金)　　##2_3_4", &Menu::物资透视::装备::护甲_金);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"消耗##2_4"))
			{
				ImGui::Checkbox(u8"武备匣　　##2_4_1", &Menu::物资透视::消耗::武备匣); ImGui::SameLine();
				ImGui::Checkbox(u8"飞索包　　##2_4_2", &Menu::物资透视::消耗::飞索包);

				ImGui::Checkbox(u8"小血丸　　##2_4_3", &Menu::物资透视::消耗::小血丸); ImGui::SameLine();
				ImGui::Checkbox(u8"大血丸　　##2_4_4", &Menu::物资透视::消耗::大血丸);

				ImGui::Checkbox(u8"小甲粉　　##2_4_5", &Menu::物资透视::消耗::小甲粉); ImGui::SameLine();
				ImGui::Checkbox(u8"大甲粉　　##2_4_6", &Menu::物资透视::消耗::大甲粉);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"属魂##2_5"))
			{
				ImGui::Checkbox(u8"攻击(白)　　##2_5_1", &Menu::物资透视::属魂::攻击_白); ImGui::SameLine();
				ImGui::Checkbox(u8"攻击(蓝)　　##2_5_2", &Menu::物资透视::属魂::攻击_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"攻击(紫)　　##2_5_3", &Menu::物资透视::属魂::攻击_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"攻击(金)　　##2_5_4", &Menu::物资透视::属魂::攻击_金);

				ImGui::Checkbox(u8"近抗(白)　　##2_5_5", &Menu::物资透视::属魂::近抗_白); ImGui::SameLine();
				ImGui::Checkbox(u8"近抗(蓝)　　##2_5_6", &Menu::物资透视::属魂::近抗_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"近抗(紫)　　##2_5_7", &Menu::物资透视::属魂::近抗_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"近抗(金)　　##2_5_8", &Menu::物资透视::属魂::近抗_金);

				ImGui::Checkbox(u8"体力(白)　　##2_5_9", &Menu::物资透视::属魂::体力_白); ImGui::SameLine();
				ImGui::Checkbox(u8"体力(蓝)　　##2_5_10", &Menu::物资透视::属魂::体力_蓝); ImGui::SameLine();
				ImGui::Checkbox(u8"体力(紫)　　##2_5_11", &Menu::物资透视::属魂::体力_紫); ImGui::SameLine();
				ImGui::Checkbox(u8"体力(金)　　##2_5_12", &Menu::物资透视::属魂::体力_金);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"特魂##2_6"))
			{
				ImGui::Checkbox(u8"妙手　　　##2_6_1", &Menu::物资透视::特魂::妙手); ImGui::SameLine();
				ImGui::Checkbox(u8"巧匠　　　##2_6_2", &Menu::物资透视::特魂::巧匠); ImGui::SameLine();
				ImGui::Checkbox(u8"凌波　　　##2_6_3", &Menu::物资透视::特魂::凌波); ImGui::SameLine();
				ImGui::Checkbox(u8"完璧　　　##2_6_4", &Menu::物资透视::特魂::完璧);

				ImGui::Checkbox(u8"光佑　　　##2_6_5", &Menu::物资透视::特魂::光佑); ImGui::SameLine();
				ImGui::Checkbox(u8"猫足　　　##2_6_6", &Menu::物资透视::特魂::猫足); ImGui::SameLine();
				ImGui::Checkbox(u8"财迷　　　##2_6_7", &Menu::物资透视::特魂::财迷); ImGui::SameLine();
				ImGui::Checkbox(u8"安神　　　##2_6_8", &Menu::物资透视::特魂::安神);

				ImGui::Checkbox(u8"毕工淌　　##2_6_9", &Menu::物资透视::特魂::毕工淌); ImGui::SameLine();
				ImGui::Checkbox(u8"吐纳术　　##2_6_10", &Menu::物资透视::特魂::吐纳术); ImGui::SameLine();
				ImGui::Checkbox(u8"虚影步　　##2_6_11", &Menu::物资透视::特魂::虚影步); ImGui::SameLine();
				ImGui::Checkbox(u8"地堂脚　　##2_6_12", &Menu::物资透视::特魂::地堂脚);

				ImGui::Checkbox(u8"天赐飞索　##2_6_13", &Menu::物资透视::特魂::天赐飞索); ImGui::SameLine();
				ImGui::Checkbox(u8"天赐武备　##2_6_14", &Menu::物资透视::特魂::天赐武备); ImGui::SameLine();
				ImGui::Checkbox(u8"燃魂一线　##2_6_15", &Menu::物资透视::特魂::燃魂一线); ImGui::SameLine();
				ImGui::Checkbox(u8"抽芯补天　##2_6_16", &Menu::物资透视::特魂::抽芯补天);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"近魂##2_7"))
			{
				ImGui::Checkbox(u8"噬魂斩　　##2_7_1", &Menu::物资透视::近魂::噬魂斩); ImGui::SameLine();
				ImGui::Checkbox(u8"青鬼　　　##2_7_2", &Menu::物资透视::近魂::青鬼); ImGui::SameLine();
				ImGui::Checkbox(u8"归元　　　##2_7_3", &Menu::物资透视::近魂::归元); ImGui::SameLine();
				ImGui::Checkbox(u8"太刀　　　##2_7_4", &Menu::物资透视::近魂::太刀);

				ImGui::Checkbox(u8"烈火斩　　##2_7_5", &Menu::物资透视::近魂::烈火斩); ImGui::SameLine();
				ImGui::Checkbox(u8"破风　　　##2_7_6", &Menu::物资透视::近魂::破风); ImGui::SameLine();
				ImGui::Checkbox(u8"裂空　　　##2_7_7", &Menu::物资透视::近魂::裂空); ImGui::SameLine();
				ImGui::Checkbox(u8"阔刀　　　##2_7_8", &Menu::物资透视::近魂::阔刀);

				ImGui::Checkbox(u8"凤凰羽　　##2_7_9", &Menu::物资透视::近魂::凤凰羽); ImGui::SameLine();
				ImGui::Checkbox(u8"蓝月　　　##2_7_10", &Menu::物资透视::近魂::蓝月); ImGui::SameLine();
				ImGui::Checkbox(u8"伏天　　　##2_7_11", &Menu::物资透视::近魂::伏天); ImGui::SameLine();
				ImGui::Checkbox(u8"长剑　　　##2_7_12", &Menu::物资透视::近魂::长剑); ImGui::SameLine();
				ImGui::Checkbox(u8"空弹　　　##2_7_13", &Menu::物资透视::近魂::空弹);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"远魂##2_8"))
			{
				ImGui::Checkbox(u8"散射　　　##2_8_1", &Menu::物资透视::远魂::散射); ImGui::SameLine();
				ImGui::Checkbox(u8"羚羊　　　##2_8_2", &Menu::物资透视::远魂::羚羊); ImGui::SameLine();
				ImGui::Checkbox(u8"爆裂　　　##2_8_3", &Menu::物资透视::远魂::爆裂); ImGui::SameLine();
				ImGui::Checkbox(u8"速射　　　##2_8_4", &Menu::物资透视::远魂::速射);

				ImGui::Checkbox(u8"精准　　　##2_8_5", &Menu::物资透视::远魂::精准); ImGui::SameLine();
				ImGui::Checkbox(u8"毒箭　　　##2_8_6", &Menu::物资透视::远魂::毒箭); ImGui::SameLine();
				ImGui::Checkbox(u8"连珠炮　　##2_8_7", &Menu::物资透视::远魂::连珠炮); ImGui::SameLine();
				ImGui::Checkbox(u8"反弹　　　##2_8_8", &Menu::物资透视::远魂::反弹);
				ImGui::Checkbox(u8"集束　　　##2_8_9", &Menu::物资透视::远魂::集束); ImGui::SameLine();
				ImGui::Checkbox(u8"落金屋　　##2_8_10", &Menu::物资透视::远魂::落金屋); ImGui::SameLine();
				ImGui::Checkbox(u8"甲破　　　##2_8_11", &Menu::物资透视::远魂::甲破);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"其他##2_6"))
			{
				ImGui::Checkbox(u8"尸盒　　　##2_6_1", &Menu::物资透视::其他::尸盒);

				ImGui::Checkbox(u8"刺梨　　　##2_6_2", &Menu::物资透视::其他::刺梨); ImGui::SameLine(); ImGui::Checkbox(u8"沙叻　　　##2_6_3", &Menu::物资透视::其他::沙叻);

				ImGui::Checkbox(u8"萤火虫　　##2_6_4", &Menu::物资透视::其他::萤火虫); ImGui::SameLine(); ImGui::Checkbox(u8"蒲公英　　##2_6_5", &Menu::物资透视::其他::蒲公英);

				ImGui::Checkbox(u8"武器扩容　##2_6_6", &Menu::物资透视::其他::武器扩容); ImGui::SameLine(); ImGui::Checkbox(u8"魂玉扩容　##2_6_7", &Menu::物资透视::其他::魂玉扩容);

				ImGui::TreePop();
			}
			ImGui::Text("\n");
			ImGui::Unindent();
		}

		if (ImGui::CollapsingHeader(((Menu::菜单设置::g_language == 0) ? (u8"玩家颜色") : ("Color"))))
		{
			ImGui::Indent();
			ImGui::ColorEdit3(((Menu::菜单设置::g_language == 0) ? (u8"骨骼") : ("Bone")), (FLOAT*)&Menu::玩家透视::透视颜色::骨骼颜色); ImGui::SameLine(180.f);
			ImGui::ColorEdit3(((Menu::菜单设置::g_language == 0) ? (u8"方框") : ("Box")), (FLOAT*)&Menu::玩家透视::透视颜色::方框颜色); ImGui::SameLine(280.f);
			ImGui::ColorEdit3(((Menu::菜单设置::g_language == 0) ? (u8"名字") : (" Name")), (FLOAT*)&Menu::玩家透视::透视颜色::名字颜色); ImGui::SameLine(380.f);
			ImGui::ColorEdit3(((Menu::菜单设置::g_language == 0) ? (u8"射线") : (" Line")), (FLOAT*)&Menu::玩家透视::透视颜色::射线颜色); ImGui::SameLine(480.f);
			ImGui::ColorEdit3(((Menu::菜单设置::g_language == 0) ? (u8"准星") : (" Quasar")), (FLOAT*)&Menu::玩家透视::透视颜色::准心颜色);
			ImGui::Text("\n");
			ImGui::Unindent();
		}
		ImGui::Unindent();
	}
}

void SetAimPlayer()
{
	if (ImGui::CollapsingHeader(((Menu::菜单设置::g_language == 0) ? (u8"瞄准") : ("AIM"))))
	{
		ImGui::Indent();
		ImGui::MenuItem(Menu::菜单设置::g_language == 0 ? (u8"自瞄启用") : ("AIM Enable"), "", &Menu::玩家瞄准::启用瞄准);
		if (Menu::玩家瞄准::启用瞄准)
		{
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"自动瞄准") : ("AimBot"), &Menu::玩家瞄准::自瞄开关::内存自瞄); ImGui::SameLine(180.f);
			ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? (u8"显示范围") : ("DrawRange"), &Menu::玩家瞄准::自瞄开关::范围开关);
			ImGui::Text(Menu::菜单设置::g_language == 0 ? u8"瞄准位置:" : "Aim Position:"); ImGui::SameLine();
			ImGui::RadioButton(Menu::菜单设置::g_language == 0 ? u8"头部" : "Head", &Menu::玩家瞄准::自瞄开关::自瞄位置, Bone::Head); ImGui::SameLine(180.f);
			ImGui::RadioButton(Menu::菜单设置::g_language == 0 ? u8"颈部" : "Neck", &Menu::玩家瞄准::自瞄开关::自瞄位置, Bone::Neck); ImGui::SameLine(280.f);
			ImGui::RadioButton(Menu::菜单设置::g_language == 0 ? u8"胸部" : "Chest", &Menu::玩家瞄准::自瞄开关::自瞄位置, Bone::Chest);

			ImGui::Text(Menu::菜单设置::g_language == 0 ? u8"瞄准热键:" : "Aim hotkeys:"); ImGui::SameLine();
			ImGui::RadioButton(Menu::菜单设置::g_language == 0 ? u8"左键" : "Left click", &Menu::玩家瞄准::自瞄开关::自瞄热键, VK_LBUTTON); ImGui::SameLine(180.f);
			ImGui::RadioButton(Menu::菜单设置::g_language == 0 ? u8"右键" : "Right click", &Menu::玩家瞄准::自瞄开关::自瞄热键, VK_RBUTTON); ImGui::SameLine(280.f);
			ImGui::RadioButton("Ctrl", &Menu::玩家瞄准::自瞄开关::自瞄热键, VK_CONTROL);
			/*			ImGui::RadioButton("Alt", &Menu::玩家瞄准::自瞄开关::自瞄热键, VK_MENU);*/

			ImGui::SliderFloatEx(Menu::菜单设置::g_language == 0 ? (u8"自瞄范围") : ("Aim Range"), (FLOAT*)&Menu::玩家瞄准::自瞄参数::m_Size, 0.f, 1000.f, "%0.f", 1.0f, ImVec2(20.f, 20.f), Menu::全局设置::白色);
			ImGui::SliderFloatEx(Menu::菜单设置::g_language == 0 ? (u8"自瞄速度") : ("Aim Speed"), (FLOAT*)&Menu::玩家瞄准::自瞄参数::m_AimSpeed, 0.f, 10.f, "%1.f", 1.0f, ImVec2(20.f, 20.f), Menu::全局设置::白色);
		}
		ImGui::Text("\n");
		ImGui::Unindent();
	}
}

uintptr_t GetInputAgentInstance() {
	auto myKit = Memory::Read<uintptr_t>(GameData::LocalPlayer::Ptr + 0xB8);
	auto InputAgent = Memory::Read<uintptr_t>(myKit + 0x20);
	return InputAgent;
}

void LeftMouseDown() {
	uintptr_t addr = Module::GameAssembly + m_LightDown;
	void(__fastcall * fnCrouchDown)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnCrouchDown = reinterpret_cast<decltype(fnCrouchDown)>(addr);
	Memory::SpoofCall(fnCrouchDown, GetInputAgentInstance(), (uintptr_t)NULL);
	/*
		typedef void(_fastcall * LightUp)(uintptr_t Rcx, uintptr_t out);
		((LightUp)(Module::GameAssembly + m_LightUp))(GetInputAgentInstance(), NULL);*/
}
void LeftMousePress() {
	uintptr_t addr = Module::GameAssembly + m_LightPress;
	void(__fastcall * fnLeftMousePress)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnLeftMousePress = reinterpret_cast<decltype(fnLeftMousePress)>(addr);
	Memory::SpoofCall(fnLeftMousePress, GetInputAgentInstance(), (uintptr_t)NULL);
}
void LeftMouseUp() {
	uintptr_t addr = Module::GameAssembly + m_LightUp;
	void(__fastcall * fnLeftMouseUp)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnLeftMouseUp = reinterpret_cast<decltype(fnLeftMouseUp)>(addr);
	Memory::SpoofCall(fnLeftMouseUp, GetInputAgentInstance(), (uintptr_t)NULL);
}
void RightMouseDown() {
	uintptr_t addr = Module::GameAssembly + m_HeavyDown;
	void(__fastcall * fnRightMouseDown)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnRightMouseDown = reinterpret_cast<decltype(fnRightMouseDown)>(addr);
	Memory::SpoofCall(fnRightMouseDown, GetInputAgentInstance(), (uintptr_t)NULL);
}
void RightMousePress() {
	uintptr_t addr = Module::GameAssembly + m_HeavyPress;
	void(__fastcall * fnRightMousePress)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnRightMousePress = reinterpret_cast<decltype(fnRightMousePress)>(addr);
	Memory::SpoofCall(fnRightMousePress, GetInputAgentInstance(), (uintptr_t)NULL);
}
void RightMouseUp() {
	uintptr_t addr = Module::GameAssembly + m_HeavyUp;
	void(__fastcall * fnRightMouseUp)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnRightMouseUp = reinterpret_cast<decltype(fnRightMouseUp)>(addr);
	Memory::SpoofCall(fnRightMouseUp, GetInputAgentInstance(), (uintptr_t)NULL);
}

void set_forward(Vector3 to) {
	uintptr_t addr = Module::GameAssembly + m_Setforward;
	uintptr_t rcx = Memory::Read<uintptr_t>(GameData::LocalPlayer::Ptr + 0x100);
	void(__fastcall * fnset_forward)(uintptr_t rcx, Vector3 to) = nullptr;
	fnset_forward = reinterpret_cast<decltype(fnset_forward)>(addr);
	return Memory::SpoofCall(fnset_forward, rcx, to);
}

FRotator get_forward(uintptr_t to) {
	uintptr_t addr = Module::GameAssembly + m_Getforward;
	uintptr_t rcx = Memory::Read<uintptr_t>(to + 0x100);
	FRotator(__fastcall * fnget_forward)(uintptr_t rcx) = nullptr;
	fnget_forward = reinterpret_cast<decltype(fnget_forward)>(addr);
	return Memory::SpoofCall(fnget_forward, rcx);
}

void DodgeDown() {
	uintptr_t addr = Module::GameAssembly + m_DodgeDown;
	void(__fastcall * fnCrouchDown)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnCrouchDown = reinterpret_cast<decltype(fnCrouchDown)>(addr);
	auto rcx = GetInputAgentInstance();
	if (!rcx || Memory::ValidPtr(rcx))
		return;
	Memory::SpoofCall(fnCrouchDown, rcx, (uintptr_t)NULL);
}
void DodgePress() {
	uintptr_t addr = Module::GameAssembly + m_DodgePress;
	void(__fastcall * fnCrouchDown)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnCrouchDown = reinterpret_cast<decltype(fnCrouchDown)>(addr);
	auto rcx = GetInputAgentInstance();
	if (!rcx || Memory::ValidPtr(rcx))
		return;
	Memory::SpoofCall(fnCrouchDown, rcx, (uintptr_t)NULL);
}
void DodgeUp() {
	uintptr_t addr = Module::GameAssembly + m_DodgeUp;
	void(__fastcall * fnCrouchDown)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnCrouchDown = reinterpret_cast<decltype(fnCrouchDown)>(addr);
	auto rcx = GetInputAgentInstance();
	if (!rcx || Memory::ValidPtr(rcx))
		return;
	Memory::SpoofCall(fnCrouchDown, rcx, (uintptr_t)NULL);
}

void JumpDown() {
	uintptr_t addr = Module::GameAssembly + m_JumpDown;
	void(__fastcall * fnJumpDown)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnJumpDown = reinterpret_cast<decltype(fnJumpDown)>(addr);
	Memory::SpoofCall(fnJumpDown, GetInputAgentInstance(), (uintptr_t)NULL);
}
void JumpPress() {
	uintptr_t addr = Module::GameAssembly + m_JumpHold;
	void(__fastcall * fnJumpPress)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnJumpPress = reinterpret_cast<decltype(fnJumpPress)>(addr);
	Memory::SpoofCall(fnJumpPress, GetInputAgentInstance(), (uintptr_t)NULL);
}
void JumpUp() {
	uintptr_t addr = Module::GameAssembly + m_JumpUP;
	void(__fastcall * fnJumpUp)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnJumpUp = reinterpret_cast<decltype(fnJumpUp)>(addr);
	Memory::SpoofCall(fnJumpUp, GetInputAgentInstance(), (uintptr_t)NULL);
}
void CrouchDown() {
	uintptr_t addr = Module::GameAssembly + m_CrouchDown;
	void(__fastcall * fnCrouchDown)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnCrouchDown = reinterpret_cast<decltype(fnCrouchDown)>(addr);
	Memory::SpoofCall(fnCrouchDown, GetInputAgentInstance(), (uintptr_t)NULL);
}
void CrouchUp() {
	uintptr_t addr = Module::GameAssembly + m_CrouchUP;
	void(__fastcall * fnCrouchUp)(uintptr_t Rcx, uintptr_t out) = nullptr;
	fnCrouchUp = reinterpret_cast<decltype(fnCrouchUp)>(addr);
	Memory::SpoofCall(fnCrouchUp, GetInputAgentInstance(), (uintptr_t)NULL);
}

/*
if (DODGE::Caster != NULL && Memory::ValidPtr(DODGE::Caster))
{
	//强制转头
	auto ObjectList = Memory::Read<uintptr_t>(DODGE::Caster + 96);
	auto ObjectEntity = Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(ObjectList + 16) + 48);
	auto EntityRootComponent = Call::GetObjectRootComponent(ObjectEntity);
	auto LocalPlayerPos = Call::ReadVector3(Call::GetMyObjRootComponent() + 0x90);
	auto ObjectPos = Call::ReadVector3(EntityRootComponent + 0x90);
	Vector3 tof = (ObjectPos - LocalPlayerPos).Normalize();
	Call::set_forward(tof);
	DODGE::Caster = NULL;
}*/

void SendKeyBoard(UINT Key, DWORD flags)
{
	INPUT input;
	memset(&input, 0, sizeof(INPUT));
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = Key;
	input.ki.wScan = MapVirtualKey(Key, 0);
	input.ki.dwFlags = flags;
	SendInput(1, &input, sizeof(INPUT));

}

void SendMouse(INT X, INT Y, DWORD flags)
{
	if (!flags)
	{
		POINT CurrentMouse;
		GetCursorPos(&CurrentMouse);
		INPUT input;
		memset(&input, 0, sizeof(INPUT));
		input.type = INPUT_MOUSE;
		input.mi.dx = X - CurrentMouse.x;
		input.mi.dy = Y - CurrentMouse.y;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		input.mi.mouseData = 0;
		input.mi.time = 0;
		input.mi.dwExtraInfo = 0;
		SendInput(1, &input, sizeof(INPUT));
	}
	else
	{
		INPUT input;
		memset(&input, 0, sizeof(INPUT));
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dwExtraInfo = 0;
		input.mi.dwFlags = flags;
		SendInput(1, &input, sizeof(INPUT));
	}
}
namespace aimbot {
	Vector3 GetVelocity(uintptr_t ActorKit)
	{
		typedef Vector3(_fastcall* Animator)(uintptr_t ptr);
		return ((Animator)(Module::GameAssembly + m_GetVelocity))(ActorKit);
	}

	Vector3 GetPrediction(uintptr_t ActorModel, Vector3 TarPos, Vector3 MyPos, int type)//预判自瞄设置
	{
		auto bulletspeed = 100;
		float gray = 0.7f;
		if (type == 1000007)
		{
			gray = 0;
			bulletspeed = 35;
		}
		if (type == 1000005) //特木耳技能
		{
			gray = 0;
			bulletspeed = bulletspeed * 0.3;
		}
		if (type == 10001)
		{
			gray = 0;
			bulletspeed = 580;
		}
		if (type == 108) //连弩
		{
			bulletspeed = bulletspeed * 0.8;
			gray = 0;
		}
		if (type == 113)//鸟铳
		{
			bulletspeed = bulletspeed * 0.7; //鸟铳
			gray = 0.0f;
		}
		if (type == 104)//弓
		{
			bulletspeed = bulletspeed * 1.6; //
			gray = 0.1f;
		}
		auto Dis = TarPos.Distance(MyPos);
		auto BulletTime = Dis / bulletspeed;

		auto tvel = GetVelocity(Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(ActorModel + 0xB8) + 0x158));

		Vector3 PredictVel; //= tvel * BulletTime;
		PredictVel.x = tvel.x * BulletTime;
		PredictVel.y = tvel.y * BulletTime;
		PredictVel.z = tvel.z * BulletTime;

		TarPos.x += PredictVel.x;
		TarPos.y += PredictVel.y;
		TarPos.z += PredictVel.z;
		auto drop = (9.81 * 0.5 * BulletTime * BulletTime) * gray;
		TarPos.y += drop;
		auto AimPos = TarPos;
		return AimPos;

		/*auto drop = 9.81 * bulletspeed * bulletspeed * Vars::Utils::BulletDrag * 1;
		TarPos.y += drop;
		auto AimPos = TarPos;
		return AimPos;*/
	}
}
VOID ZhenDaoThread()
{
	//主线程
}

LRESULT ZhenDaoWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == ZhenDaoMessage_1)
	{
		if (GameData::LocalPlayer::ActorKit != NULL)
		{

			uintptr_t Parameter = Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Module::GameAssembly + 0x724DFC0) + 0xB8));
			//uintptr_t Parameter = Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Module::GameAssembly + 0x67D5648) + 0xB8));
			if (Parameter)
			{
				//内存震刀写这//内存震刀写这//内存震刀写这//内存震刀写这//内存震刀写这//内存震刀写这//内存震刀写这//内存震刀写这

				//RightMouseDown();
				//LeftMouseDown();


				//LeftMousePress();
				//RightMousePress();


				//LeftMouseUp();
				//RightMouseUp();



				
			}
		}
	}

	return CallWindowProcA(ZhenDao::GameWndProc, hWnd, uMsg, wParam, lParam);
}

VOID SetFunction()
{
	if (ImGui::CollapsingHeader(((Menu::菜单设置::g_language == 0) ? (u8"稳定功能") : ("Function"))))
	{
		ImGui::Indent();

		if (ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? u8"强制震刀 F6" : "Forced shock knife", &Menu::功能设置::功能开关::强制震刀))
		{
			
		}ImGui::SameLine(); ImGui::HelpMarker(Menu::菜单设置::g_language == 0 ? u8"如果点击菜单无效，请按键盘 F6 进行开关操作///设置延时无效 请按小键盘左键降低延时，右键增加延时" : "如果点击菜单无效，请按键盘 F6 进行开关操作///设置延时无效 请按小键盘←左键降低延时，→右键增加延时");

		if (ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? u8"反震升龙 F7" : "	Shock Thang Long", &Menu::功能设置::功能开关::反震升龙))
		{
			
		}ImGui::SameLine(); ImGui::HelpMarker(Menu::菜单设置::g_language == 0 ? u8"如果点击菜单无效，请按键盘 F7 进行开关操作" : "如果点击菜单无效，请按键盘 F7 进行开关操作");
		/*if (ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? u8"自动连招" : "	Automatic combo", &Menu::功能设置::功能开关::自动连招))
		{

		}*/
		if (ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? u8"无限精力 F8" : "	Unlimited energy", &Menu::功能设置::功能开关::无限精力))
		{
			
		}ImGui::SameLine(); ImGui::HelpMarker(Menu::菜单设置::g_language == 0 ? u8"如果点击菜单无效，请按键盘 F8 进行开关操作" : "如果点击菜单无效，请按键盘 F8 进行开关操作");
		
		
		ImGui::Text("\n");
		ImGui::Unindent();
	}
	if (ImGui::CollapsingHeader(((Menu::菜单设置::g_language == 0) ? (u8"变态功能") : ("Function"))))
	{
		ImGui::Indent();
		if (ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? u8"凌波微步" : "	The Limbo", &Menu::功能设置::功能开关::凌波微步))
		{

		} ImGui::SameLine(); ImGui::HelpMarker(Menu::菜单设置::g_language == 0 ? u8"无限的精力无限的闪避无限的位移" : "Infinite energy infinite dodge infinite displacement");

		if (ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? u8"逆天改命" : "Changing the fate of the world", &Menu::功能设置::功能开关::逆天改命))
		{

		} ImGui::SameLine(); ImGui::HelpMarker(Menu::菜单设置::g_language == 0 ? u8"当自身濒死时自动闪现到安全位置" : "Automatically flash to a safe position when you are on the verge of death");

		if (ImGui::CheckboxEx(Menu::菜单设置::g_language == 0 ? u8"瞬移秒杀" : "instant kill", &Menu::功能设置::功能开关::飞龙缠身))
		{

		} ImGui::SameLine(); ImGui::HelpMarker(Menu::菜单设置::g_language == 0 ? u8"建议在使用阔剑的时候，用右键积累力量，以达到最佳效果。\n\n请不要太激进，因为这个功能太变态了，可能会被举报。" : "It is recommended to use the broadsword with the right click to accumulate power for best results\n\nPlease do not be too aggressive as this feature is too perverse and may be reported");
		ImGui::Text("\n");
		ImGui::Unindent();
	}
}

Vector2 WorldToScreen(Vector3 WorldLocation)
{
	Vector2 Result = Vector2{ -g_d3dViewPort.TopLeftX, -g_d3dViewPort.TopLeftY };

	D3DMATRIX MatrixData = Memory::Read<D3DMATRIX>(Memory::Read<ULONG64>(GameData::Base::Matrix + Matrix_2) + Matrix_3);

	FLOAT View = MatrixData._14 * WorldLocation.x + MatrixData._24 * WorldLocation.y + MatrixData._34 * WorldLocation.z + MatrixData._44;

	if (View >= 0.01f)
	{
		View = 1.f / View;

		Result.x = g_d3dViewPort.TopLeftX + (MatrixData._11 * WorldLocation.x + MatrixData._21 * WorldLocation.y + MatrixData._31 * WorldLocation.z + MatrixData._41) * View * g_d3dViewPort.TopLeftX;

		Result.y = g_d3dViewPort.TopLeftY - (MatrixData._12 * WorldLocation.x + MatrixData._22 * WorldLocation.y + MatrixData._32 * WorldLocation.z + MatrixData._42) * View * g_d3dViewPort.TopLeftY;
	}

	return Result;
}

BOOL WorldToScreen(Vector3* vOrigin)
{
	Vector3 WorldLocation = *vOrigin;
	D3DMATRIX MatrixData = Memory::Read<D3DMATRIX>(Memory::Read<ULONG64>(GameData::Base::Matrix + Matrix_2) + Matrix_3);
	FLOAT View = MatrixData._14 * WorldLocation.x + MatrixData._24 * WorldLocation.y + MatrixData._34 * WorldLocation.z + MatrixData._44;
	if (View >= 0.01f)
	{
		View = 1.f / View;
		vOrigin->x = g_d3dViewPort.TopLeftX + (MatrixData._11 * WorldLocation.x + MatrixData._21 * WorldLocation.y + MatrixData._31 * WorldLocation.z + MatrixData._41) * View * g_d3dViewPort.TopLeftX;

		vOrigin->y = g_d3dViewPort.TopLeftY - (MatrixData._12 * WorldLocation.x + MatrixData._22 * WorldLocation.y + MatrixData._32 * WorldLocation.z + MatrixData._42) * View * g_d3dViewPort.TopLeftY;
		return TRUE;
	}
	return FALSE;
}

Vector3 GetBonePosition(ULONG64 PlayerPtr, ULONG BoneID)
{
	ULONG64 ActorKit = Memory::Read<ULONG64>(PlayerPtr + 0xB8);

	if (!Memory::ValidPtr(ActorKit))
	{
		ULONG64 AnimatorComponent = Memory::Read<ULONG64>(ActorKit + 0x158);

		if (!Memory::ValidPtr(AnimatorComponent))
		{
			ULONG64 BoneTransform = UnityEngine::GetBoneTransform(AnimatorComponent, BoneID);

			if (!Memory::ValidPtr(BoneTransform))
			{
				return UnityEngine::TransformToWorld(BoneTransform);
			}
		}
	}

	return Vector3{ 0.f, 0.f, 0.f };
}

PCWCH GetPlayerName(ULONG64 StatePtr)
{
	PCWCH Result = NULL;

	ULONG64 Temp_1 = Memory::Read<ULONG64>(StatePtr + 0xF8);

	if (!Memory::ValidPtr(Temp_1))
	{
		Result = (LPCWCH)(Temp_1 + 0x14);
	}

	return Result;
}

ULONG GetPlayerTeam(ULONG64 StatePtr)
{
	return Memory::Read<ULONG>(StatePtr + 0xC0);
}

UCHAR GetPlayerAttack(ULONG64 PlayerPtr)
{
	ULONG64 ActorKit = Memory::Read<ULONG64>(PlayerPtr + 0xB8);

	if (!Memory::ValidPtr(ActorKit))
	{
		ULONG64 AnimPlayableAgent = Memory::Read<ULONG64>(ActorKit + 0x1E0);

		if (!Memory::ValidPtr(AnimPlayableAgent))
		{
			ULONG64 PlaybleTrackDriver = Memory::Read<ULONG64>(AnimPlayableAgent + 0x68);

			if (!Memory::ValidPtr(PlaybleTrackDriver))
			{
				ULONG64 FrameBaseLayerCrossFade = Memory::Read<ULONG64>(PlaybleTrackDriver + 0x18);

				if (!Memory::ValidPtr(FrameBaseLayerCrossFade))
				{
					return Memory::Read<UCHAR>(FrameBaseLayerCrossFade + 0x141);
				}
			}
		}
	}

	return NULL;
}

FLOAT GetPlayerXuLiTime(ULONG64 PlayerPtr)
{
	FLOAT Result = 0.f;

	ULONG64 Temp_1 = Memory::Read<ULONG64>(PlayerPtr + 0xB8);

	if (Temp_1)
	{
		ULONG64 Temp_2 = Memory::Read<ULONG64>(Temp_1 + 0x38);

		if (Temp_2)
		{
			ULONG64 Temp_3 = Memory::Read<ULONG64>(Temp_2 + 0x18);

			if (Temp_3)
			{
				ULONG64 Temp_4 = Memory::Read<ULONG64>(Temp_3 + 0x18);

				if (Temp_4)
				{
					return *(FLOAT*)(*(ULONG64*)(Temp_4 + 0x10) + 4 * 12 + 0x20);
				}
			}
		}
	}

	return Result;
}

VOID WritePlayerXuLiTime(ULONG64 PlayerPtr, FLOAT XuLiTime)
{
	ULONG64 Temp_1 = Memory::Read<ULONG64>(PlayerPtr + 0xB8);

	if (Temp_1)
	{
		ULONG64 Temp_2 = Memory::Read<ULONG64>(Temp_1 + 0x38);

		if (Temp_2)
		{
			ULONG64 Temp_3 = Memory::Read<ULONG64>(Temp_2 + 0x18);

			if (Temp_3)
			{
				ULONG64 Temp_4 = Memory::Read<ULONG64>(Temp_3 + 0x18);

				if (Temp_4)
				{
					*(FLOAT*)(*(ULONG64*)(Temp_4 + 0x10) + 4 * 12 + 0x20) = XuLiTime;
				}
			}
		}
	}
}

ULONG GetAttackSleepTime(ULONG64 PlayerPtr, FLOAT WeaponId, FLOAT Distance)
{
	ULONG64 ActorKit = Memory::Read<ULONG64>(PlayerPtr + 0xB8);

	if (!Memory::ValidPtr(ActorKit))
	{
		ULONG64 AnimPlayableAgent = Memory::Read<ULONG64>(ActorKit + 0x1E0);

		if (!Memory::ValidPtr(AnimPlayableAgent))
		{
			ULONG64 PlaybleTrackDriver = Memory::Read<ULONG64>(AnimPlayableAgent + 0x68);

			if (!Memory::ValidPtr(PlaybleTrackDriver))
			{
				ULONG64 ObjectMessager = Memory::Read<ULONG64>(PlaybleTrackDriver + 0x28);

				if (!Memory::ValidPtr(ObjectMessager))
				{
					ULONG64 EventTracksForLayer = Memory::Read<ULONG64>(ObjectMessager + 0x20);

					if (!Memory::ValidPtr(EventTracksForLayer))
					{
						ULONG64 EventTrackSet = Memory::Read<ULONG64>(EventTracksForLayer + 0x20);

						if (!Memory::ValidPtr(EventTrackSet))
						{
							PWCHAR AnimClipName = (PWCHAR)(Memory::Read<ULONG64>(EventTrackSet + 0x10) + 0x14);

							if (!IsBadStringPtrW(AnimClipName, MAX_PATH))
							{
								if (WeaponId == WeaponId::长剑)
								{
									if (wcsstr(AnimClipName, L"male_sw_"))
									{
										if (!wcscmp(AnimClipName, L"male_sw_emptystep_back_01")) { return 9999; } /*站震*/
										if (!wcscmp(AnimClipName, L"male_sw_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										if (!wcscmp(AnimClipName, L"male_sw_attack_light_03")) { return (ULONG)(50 + Distance * 10); } /*左键三段*/
										if (!wcscmp(AnimClipName, L"male_sw_attack_heavy_03")) { return (ULONG)(50 + Distance * 10); } /*右键三段*/
										if (!wcscmp(AnimClipName, L"male_sw_attack_light_copy_03")) { return (ULONG)(100 + Distance * 10); } /*左键三段-蓝月*/
										if (!wcscmp(AnimClipName, L"male_sw_attack_heavy_copy_03")) { return (ULONG)(100 + Distance * 10); } /*右键三段-蓝月*/
										if (!wcscmp(AnimClipName, L"male_sw_attack_hold_light_01")) { return (ULONG)(50 + Distance * 10); } /*左键蓄力*/
										if (!wcscmp(AnimClipName, L"male_sw_attack_hold_heavy_01")) { return (ULONG)(50 + Distance * 10); } /*右键蓄力*/
										if (!wcscmp(AnimClipName, L"male_sw_attack_hold_light_soul_01")) { return (ULONG)(100 + Distance * 10); } /*左键蓄力-凤凰羽*/
										if (!wcscmp(AnimClipName, L"male_sw_attack_hold_heavy_soul_01")) { return (ULONG)(100 + Distance * 10); } /*右键蓄力-凤凰羽*/
									}

									if (wcsstr(AnimClipName, L"female_sw_"))
									{
										if (!wcscmp(AnimClipName, L"female_sw_emptystep_back_01")) { return 9999; } /*站震*/
										if (!wcscmp(AnimClipName, L"female_sw_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										if (!wcscmp(AnimClipName, L"female_sw_attack_light_03")) { return (ULONG)(50 + Distance * 10); } /*左键三段*/
										if (!wcscmp(AnimClipName, L"female_sw_attack_heavy_03")) { return (ULONG)(50 + Distance * 10); } /*右键三段*/
										if (!wcscmp(AnimClipName, L"female_sw_attack_light_copy_03")) { return (ULONG)(100 + Distance * 10); } /*左键三段-蓝月*/
										if (!wcscmp(AnimClipName, L"female_sw_attack_heavy_copy_03")) { return (ULONG)(100 + Distance * 10); } /*右键三段-蓝月*/
										if (!wcscmp(AnimClipName, L"female_sw_attack_hold_light_01")) { return (ULONG)(50 + Distance * 10); } /*左键蓄力*/
										if (!wcscmp(AnimClipName, L"female_sw_attack_hold_heavy_01")) { return (ULONG)(50 + Distance * 10); } /*右键蓄力*/
										if (!wcscmp(AnimClipName, L"female_sw_attack_hold_light_soul_01")) { return (ULONG)(100 + Distance * 10); } /*左键蓄力-凤凰羽*/
										if (!wcscmp(AnimClipName, L"female_sw_attack_hold_heavy_soul_01")) { return (ULONG)(100 + Distance * 10); } /*右键蓄力-凤凰羽*/
									}
								}

								if (WeaponId == WeaponId::匕首)
								{
									if (wcsstr(AnimClipName, L"male_dagger_"))
									{
										if (!wcscmp(AnimClipName, L"male_dagger_emptystep_back_01")) { return 9999; } /*站震*/
										if (!wcscmp(AnimClipName, L"male_dagger_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										if (!wcscmp(AnimClipName, L"male_dagger_attack_light_03")) { return (ULONG)(200 + Distance * 10); } /*左键三段*/
										if (!wcscmp(AnimClipName, L"male_dagger_attack_heavy_03")) { return (ULONG)(200 + Distance * 10); } /*右键三段*/
										if (!wcscmp(AnimClipName, L"male_dagger_attack_hold_light_01")) { return (ULONG)(50 + Distance * 10); } /*左键蓄力*/
										if (!wcscmp(AnimClipName, L"male_dagger_attack_hold_heavy_01")) { return (ULONG)(10 + Distance * 15); } /*右键蓄力*/
										if (!wcscmp(AnimClipName, L"male_dagger_flashstep_attack_light_01")) { return (ULONG)(150 + Distance * 15); } /*左键突进-鬼反断*/
										if (!wcscmp(AnimClipName, L"male_dagger_attack_hold_heavy_soul_01")) { return (ULONG)(150 + Distance * 15); } /*右键蓄力-鬼刃暗扎*/
									}

									if (wcsstr(AnimClipName, L"female_dagger_"))
									{
										if (!wcscmp(AnimClipName, L"female_dagger_emptystep_back_01")) { return 9999; } /*站震*/
										if (!wcscmp(AnimClipName, L"female_dagger_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										if (!wcscmp(AnimClipName, L"female_dagger_attack_light_03")) { return (ULONG)(200 + Distance * 10); } /*左键三段*/
										if (!wcscmp(AnimClipName, L"female_dagger_attack_heavy_03")) { return (ULONG)(200 + Distance * 10); } /*右键三段*/
										if (!wcscmp(AnimClipName, L"female_dagger_attack_hold_light_01")) { return (ULONG)(50 + Distance * 10); } /*左键蓄力*/
										if (!wcscmp(AnimClipName, L"female_dagger_attack_hold_heavy_01")) { return (ULONG)(10 + Distance * 15); } /*右键蓄力*/
										if (!wcscmp(AnimClipName, L"female_dagger_flashstep_attack_light_01")) { return (ULONG)(150 + Distance * 15); } /*左键突进-鬼反断*/
										if (!wcscmp(AnimClipName, L"female_dagger_attack_hold_heavy_soul_01")) { return (ULONG)(150 + Distance * 15); } /*右键蓄力-鬼刃暗扎*/
									}
								}

								if (WeaponId == WeaponId::长枪)
								{
									if (wcsstr(AnimClipName, L"male_spear_"))
									{
										if (!wcscmp(AnimClipName, L"male_spear_emptystep_back_01")) { return 9999; } /*站震*/
										if (!wcscmp(AnimClipName, L"male_spear_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_light_03")) { return (ULONG)(175 + Distance * 10); } /*左键三段*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_heavy_03")) { return (ULONG)(175 + Distance * 10); } /*右键三段*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_light_soul_03")) { return (ULONG)(175 + Distance * 10); } /*左键三段-双环扫*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_heavy_soul_03")) { return (ULONG)(100 + Distance * 10); } /*右键三段-风卷残云*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_hold_light_01")) { return (ULONG)(100 + Distance * 10); } /*左键蓄力*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_hold_heavy_01")) { return (ULONG)(100 + Distance * 10); } /*右键蓄力*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_hold_light_03")) { return (ULONG)(50 + Distance * 10); } /*左键蓄力-龙王破*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_hold_heavy_03")) { return (ULONG)(50 + Distance * 10); } /*右键蓄力-龙王破*/
										if (!wcscmp(AnimClipName, L"male_spear_attack_hold_heavy_soul_01")) { return (ULONG)(50 + Distance * 10); } /*右键蓄力-大圣游*/
									}

									if (wcsstr(AnimClipName, L"female_spear_"))
									{
										if (!wcscmp(AnimClipName, L"female_spear_emptystep_back_01")) { return 9999; } /*站震*/
										if (!wcscmp(AnimClipName, L"female_spear_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_light_03")) { return (ULONG)(175 + Distance * 10); } /*左键三段*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_heavy_03")) { return (ULONG)(175 + Distance * 10); } /*右键三段*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_light_soul_03")) { return (ULONG)(175 + Distance * 10); } /*左键三段-双环扫*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_heavy_soul_03")) { return (ULONG)(100 + Distance * 10); } /*右键三段-风卷残云*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_hold_light_01")) { return (ULONG)(100 + Distance * 10); } /*左键蓄力*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_hold_heavy_01")) { return (ULONG)(100 + Distance * 10); } /*右键蓄力*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_hold_light_03")) { return (ULONG)(50 + Distance * 10); } /*左键蓄力-龙王破*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_hold_heavy_03")) { return (ULONG)(50 + Distance * 10); } /*右键蓄力-龙王破*/
										if (!wcscmp(AnimClipName, L"female_spear_attack_hold_heavy_soul_01")) { return (ULONG)(100 + Distance * 10); } /*右键蓄力-大圣游*/
									}
								}

								if (WeaponId == WeaponId::太刀)
								{
									if (wcsstr(AnimClipName, L"male_katana_"))
									{
										if (!wcscmp(AnimClipName, L"male_katana_emptystep_back_01")) { return 9999; } /*站震*/
										if (!wcscmp(AnimClipName, L"male_katana_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_light_03")) { return (ULONG)(50 + Distance * 10); } /*左键三段*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_heavy_03")) { return (ULONG)(50 + Distance * 10); } /*右键三段*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_light_soul_03")) { return (ULONG)(50 + Distance * 10); } /*左键三段-青鬼*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_heavy_soul_03")) { return (ULONG)(50 + Distance * 10); } /*右键三段-青鬼*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_hold_light_01")) { return (ULONG)(0 + Distance * 10); } /*左键蓄力-Lv.1*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_hold_heavy_01")) { return (ULONG)(0 + Distance * 10); } /*右键蓄力-Lv.1*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_hold_light_02")) { return (ULONG)(0 + Distance * 10); } /*左键蓄力-Lv.2*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_hold_heavy_02")) { return (ULONG)(0 + Distance * 10); } /*右键蓄力-Lv.2*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_hold_light_soul_02")) { return (ULONG)(0 + Distance * 10); } /*左键蓄力-噬魂斩*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_hold_heavy_soul_02")) { return (ULONG)(0 + Distance * 10); } /*右键蓄力-噬魂斩*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_light_05")) { return (ULONG)(100 + Distance * 15); } /*左键蓄力-追加*/
										if (!wcscmp(AnimClipName, L"male_katana_attack_heavy_09")) { return (ULONG)(100 + Distance * 15); } /*右键蓄力-追加*/
									}

									if (wcsstr(AnimClipName, L"female_katana_"))
									{
										if (!wcscmp(AnimClipName, L"female_katana_emptystep_back_01")) { return 9999; } /*站震*/
										if (!wcscmp(AnimClipName, L"female_katana_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_light_03")) { return (ULONG)(50 + Distance * 10); } /*左键三段*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_heavy_03")) { return (ULONG)(50 + Distance * 10); } /*右键三段*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_light_soul_03")) { return (ULONG)(50 + Distance * 10); } /*左键三段-青鬼*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_heavy_soul_03")) { return (ULONG)(50 + Distance * 10); } /*右键三段-青鬼*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_hold_light_01")) { return (ULONG)(0 + Distance * 10); } /*左键蓄力-Lv.1*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_hold_heavy_01")) { return (ULONG)(0 + Distance * 10); } /*右键蓄力-Lv.1*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_hold_light_02")) { return (ULONG)(0 + Distance * 10); } /*左键蓄力-Lv.2*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_hold_heavy_02")) { return (ULONG)(0 + Distance * 10); } /*右键蓄力-Lv.2*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_hold_light_soul_02")) { return (ULONG)(0 + Distance * 10); } /*左键蓄力-噬魂斩*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_hold_heavy_soul_02")) { return (ULONG)(0 + Distance * 10); } /*右键蓄力-噬魂斩*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_light_05")) { return (ULONG)(100 + Distance * 15); } /*左键蓄力-追加*/
										if (!wcscmp(AnimClipName, L"female_katana_attack_heavy_09")) { return (ULONG)(100 + Distance * 15); } /*右键蓄力-追加*/
									}
								}

								if (WeaponId == WeaponId::阔刀)
								{
									if (wcsstr(AnimClipName, L"male_blade_"))
									{
										if (wcsstr(AnimClipName, L"male_blade_"))
										{
											if (!wcscmp(AnimClipName, L"male_blade_emptystep_back_01")) { return 9999; } /*站震*/
											if (!wcscmp(AnimClipName, L"male_blade_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										}

										if (wcsstr(AnimClipName, L"male_blade_attack_light_"))
										{
											if (!wcscmp(AnimClipName, L"male_blade_attack_light_01")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_light_02")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_light_06")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_light_07")) { return (ULONG)(250 + Distance * 10); }
										}

										if (wcsstr(AnimClipName, L"male_blade_attack_heavy_"))
										{
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_02")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_03")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_04")) { return (ULONG)(250 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_05")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_05_2")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_05_3")) { return (ULONG)(100 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_06")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_06_2")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_06_3")) { return (ULONG)(100 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_07")) { return (ULONG)(250 + Distance * 15); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_07_2")) { return (ULONG)(250 + Distance * 15); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_07_3")) { return (ULONG)(250 + Distance * 15); }

											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_02")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_04")) { return (ULONG)(250 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_05")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_05_2")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_05_3")) { return (ULONG)(200 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_06")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_06_2")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_06_3")) { return (ULONG)(200 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_07")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_07_2")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"male_blade_attack_heavy_copy_07_3")) { return (ULONG)(250 + Distance * 10); }
										}

										if (wcsstr(AnimClipName, L"male_blade_attack_hold_"))
										{
											if (!wcscmp(AnimClipName, L"male_blade_attack_hold_light_01")) { return (ULONG)(100 + Distance * 10); } /*左键蓄力Lv.1*/
											if (!wcscmp(AnimClipName, L"male_blade_attack_hold_light_02")) { return (ULONG)(50 + Distance * 10); } /*左键蓄力Lv.2*/
											if (!wcscmp(AnimClipName, L"male_blade_attack_hold_light_03")) { return (ULONG)(50 + Distance * 15); } /*左键蓄力Lv.3*/
											if (!wcscmp(AnimClipName, L"male_blade_attack_hold_light_copy_02")) { return (ULONG)(150 + Distance * 15); } /*左键蓄力-烈火斩*/
											if (!wcscmp(AnimClipName, L"male_blade_attack_hold_light_soul_03_1")) { return (ULONG)(100 + Distance * 25); } /*左键蓄力-震雷刀*/
										}
									}

									if (wcsstr(AnimClipName, L"female_blade_"))
									{
										if (wcsstr(AnimClipName, L"female_blade_"))
										{
											if (!wcscmp(AnimClipName, L"female_blade_emptystep_back_01")) { return 9999; } /*站震*/
											if (!wcscmp(AnimClipName, L"female_blade_jump_emptystep_back_02")) { return 9999; } /*跳震*/
										}

										if (wcsstr(AnimClipName, L"female_blade_attack_light_"))
										{
											if (!wcscmp(AnimClipName, L"female_blade_attack_light_01")) { return (ULONG)(150 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_light_02")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_light_06")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_light_07")) { return (ULONG)(250 + Distance * 10); }
										}

										if (wcsstr(AnimClipName, L"female_blade_attack_heavy_"))
										{
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_02")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_03")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_04")) { return (ULONG)(250 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_05")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_05_2")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_05_3")) { return (ULONG)(100 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_06")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_06_2")) { return (ULONG)(100 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_06_3")) { return (ULONG)(100 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_07")) { return (ULONG)(200 + Distance * 15); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_07_2")) { return (ULONG)(200 + Distance * 15); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_07_3")) { return (ULONG)(200 + Distance * 15); }

											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_02")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_04")) { return (ULONG)(200 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_05")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_05_2")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_05_3")) { return (ULONG)(200 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_06")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_06_2")) { return (ULONG)(200 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_06_3")) { return (ULONG)(200 + Distance * 10); }

											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_07")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_07_2")) { return (ULONG)(250 + Distance * 10); }
											if (!wcscmp(AnimClipName, L"female_blade_attack_heavy_copy_07_3")) { return (ULONG)(25 + Distance * 10); }
										}

										if (wcsstr(AnimClipName, L"female_blade_attack_hold_"))
										{
											if (!wcscmp(AnimClipName, L"female_blade_attack_hold_light_01")) { return (ULONG)(100 + Distance * 10); } /*左键蓄力Lv.1*/
											if (!wcscmp(AnimClipName, L"female_blade_attack_hold_light_02")) { return (ULONG)(50 + Distance * 10); } /*左键蓄力Lv.2*/
											if (!wcscmp(AnimClipName, L"female_blade_attack_hold_light_03")) { return (ULONG)(50 + Distance * 15); } /*左键蓄力Lv.3*/
											if (!wcscmp(AnimClipName, L"female_blade_attack_hold_light_copy_02")) { return (ULONG)(150 + Distance * 15); } /*左键蓄力-烈火斩*/
											if (!wcscmp(AnimClipName, L"female_blade_attack_hold_light_soul_03_1")) { return (ULONG)(100 + Distance * 25); } /*左键蓄力-震雷刀*/
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return NULL;
}

LPCWCH GetLastAnimClipName(ULONG64 PlayerPtr)
{
	ULONG64 ActorKit = Memory::Read<ULONG64>(PlayerPtr + 0xB8);

	if (!Memory::ValidPtr(ActorKit))
	{
		ULONG64 AnimPlayableAgent = Memory::Read<ULONG64>(ActorKit + 0x1E0);

		if (!Memory::ValidPtr(AnimPlayableAgent))
		{
			ULONG64 PlaybleTrackDriver = Memory::Read<ULONG64>(AnimPlayableAgent + 0x68);

			if (!Memory::ValidPtr(PlaybleTrackDriver))
			{
				ULONG64 ObjectMessager = Memory::Read<ULONG64>(PlaybleTrackDriver + 0x28);

				if (!Memory::ValidPtr(ObjectMessager))
				{
					ULONG64 EventTracksForLayer = Memory::Read<ULONG64>(ObjectMessager + 0x20);

					if (!Memory::ValidPtr(EventTracksForLayer))
					{
						ULONG64 EventTrackSet = Memory::Read<ULONG64>(EventTracksForLayer + 0x20);

						if (!Memory::ValidPtr(EventTrackSet))
						{
							ULONG64 AnimClipName = Memory::Read<ULONG64>(EventTrackSet + 0x10);

							if (!Memory::ValidPtr(AnimClipName))
							{
								return (LPCWCH)(AnimClipName + 0x14);
							}
						}
					}
				}
			}
		}
	}

	return NULL;
}

FItemData GetItemData(ULONG64 ItemId)
{
	switch (ItemId)
	{
	case 3040002:
		return FItemData{ 1, 0, 0 }; //尸盒
	case 3010001:
		return FItemData{ 1, 0, 0 }; //魂玉扩容
	case 3010002:
		return FItemData{ 1, 0, 0 }; //武器扩容
	case 3010007:
		return FItemData{ 1, 0, 0 }; //蒲公英
	case 3010008:
		return FItemData{ 1, 0, 0 }; //刺梨
	case 3010009:
		return FItemData{ 1, 0, 0 }; //沙叻
	case 3010004:
		return FItemData{ 1, 0, 0 }; //凝血丸(小)
	case 3010006:
		return FItemData{ 1, 0, 1 }; //凝血丸(大)
	case 3010023:
		return FItemData{ 2, 0, 0 }; //护甲粉末(小)
	case 3010024:
		return FItemData{ 2, 0, 1 }; //护甲粉末(大)
	case 3010018:
		return FItemData{ 3, 1, 0 }; //武备匣
	case 3010020:
		return FItemData{ 4, 1, 1 }; //飞索线轴
	case 3000001:
		return FItemData{ 5, 0, 0 }; //长剑(白)
	case 3000011:
		return FItemData{ 5, 0, 1 }; //长剑(蓝)
	case 3000021:
		return FItemData{ 5, 0, 2 }; //长剑(紫)
	case 3000031:
		return FItemData{ 5, 0, 3 }; //长剑(金)
	case 3000200:
		return FItemData{ 5, 0, 0 }; //长枪(白)
	case 3000210:
		return FItemData{ 5, 0, 1 }; //长枪(蓝)
	case 3000220:
		return FItemData{ 5, 0, 2 }; //长枪(紫)
	case 3000230:
		return FItemData{ 5, 0, 3 }; //长枪(金)
	case 3000300:
		return FItemData{ 5, 0, 0 }; //太刀(白)
	case 3000310:
		return FItemData{ 5, 0, 1 }; //太刀(蓝)
	case 3000320:
		return FItemData{ 5, 0, 2 }; //太刀(紫)
	case 3000330:
		return FItemData{ 5, 0, 3 }; //太刀(金)
	case 3000400:
		return FItemData{ 5, 0, 0 }; //阔刀(白)
	case 3000410:
		return FItemData{ 5, 0, 1 }; //阔刀(蓝)
	case 3000420:
		return FItemData{ 5, 0, 2 }; //阔刀(紫)
	case 3000430:
		return FItemData{ 5, 0, 3 }; //阔刀(金)
	case 3000501:
		return FItemData{ 5, 1, 0 }; //弓箭(白)
	case 3000511:
		return FItemData{ 5, 1, 1 }; //弓箭(蓝)
	case 3000521:
		return FItemData{ 5, 1, 2 }; //弓箭(紫)
	case 3000531:
		return FItemData{ 5, 1, 3 }; //弓箭(金)
	case 3000700:
		return FItemData{ 5, 1, 0 }; //连弩(白)
	case 3000710:
		return FItemData{ 5, 1, 1 }; //连弩(蓝)
	case 3000720:
		return FItemData{ 5, 1, 2 }; //连弩(紫)
	case 3000730:
		return FItemData{ 5, 1, 3 }; //连弩(金)
	case 3000800:
		return FItemData{ 5, 1, 0 }; //火炮(白)
	case 3000810:
		return FItemData{ 5, 1, 1 }; //火炮(蓝)
	case 3000820:
		return FItemData{ 5, 1, 2 }; //火炮(紫)
	case 3000830:
		return FItemData{ 5, 1, 3 }; //火炮(金)
	case 3000900:
		return FItemData{ 5, 1, 0 }; //喷火筒(白)
	case 3000910:
		return FItemData{ 5, 1, 1 }; //喷火筒(蓝)
	case 3000920:
		return FItemData{ 5, 1, 2 }; //喷火筒(紫)
	case 3000930:
		return FItemData{ 5, 1, 3 }; //喷火筒(金)
	case 3001000:
		return FItemData{ 5, 1, 0 }; //壹蜂窝(白)
	case 3001010:
		return FItemData{ 5, 1, 1 }; //壹蜂窝(蓝)
	case 3001020:
		return FItemData{ 5, 1, 2 }; //壹蜂窝(紫)
	case 3001030:
		return FItemData{ 5, 1, 3 }; //壹蜂窝(金)
	case 3001100:
		return FItemData{ 5, 1, 0 }; //五眼统(白)
	case 3001110:
		return FItemData{ 5, 1, 1 }; //五眼统(蓝)
	case 3001120:
		return FItemData{ 5, 1, 2 }; //五眼统(紫)
	case 3001130:
		return FItemData{ 5, 1, 3 }; //五眼统(金)
	case 3001200:
		return FItemData{ 5, 1, 0 }; //鸟统(白)
	case 3001210:
		return FItemData{ 5, 1, 1 }; //鸟统(蓝)
	case 3001220:
		return FItemData{ 5, 1, 2 }; //鸟统(紫)
	case 3001230:
		return FItemData{ 5, 1, 3 }; //鸟统(金)
	case 3005001:
		return FItemData{ 5, 2, 0 }; //护甲(白)
	case 3005002:
		return FItemData{ 5, 2, 0 }; //护甲(蓝)
	case 3005003:
		return FItemData{ 5, 2, 0 }; //护甲(紫)
	case 3005004:
		return FItemData{ 5, 2, 0 }; //护甲(金)
	default:
		return FItemData{ NULL, NULL, NULL };
	}
}

FWeaponData GetWeaponData(ULONG64 StatePtr)
{
	switch (Memory::Read<ULONG>(StatePtr + ActorState_WeaponId_1))
	{
	case 3200001:
		return FWeaponData{ 1, 1, 1 };  //长剑(白)
	case 3200011:
		return FWeaponData{ 1, 1, 2 };  //长剑(蓝)
	case 3200021:
		return FWeaponData{ 1, 1, 3 };  //长剑(紫)
	case 3200031:
		return FWeaponData{ 1, 1, 4 };  //长剑(金)
	case 3200101:
		return FWeaponData{ 2, 1, 1 };  //匕首(白)
	case 3200111:
		return FWeaponData{ 2, 1, 2 };  //匕首(蓝)
	case 3200121:
		return FWeaponData{ 2, 1, 3 };  //匕首(紫)
	case 3200131:
		return FWeaponData{ 2, 1, 4 };  //匕首(金)
	case 3200200:
		return FWeaponData{ 3, 1, 1 };  //长抢(白)
	case 3200210:
		return FWeaponData{ 3, 1, 2 };  //长抢(蓝)
	case 3200220:
		return FWeaponData{ 3, 1, 3 };  //长抢(紫)
	case 3200230:
		return FWeaponData{ 3, 1, 4 };  //长抢(金)
	case 3200300:
		return FWeaponData{ 4, 1, 1 };  //太刀(白)
	case 3200310:
		return FWeaponData{ 4, 1, 2 };  //太刀(蓝)
	case 3200320:
		return FWeaponData{ 4, 1, 3 };  //太刀(紫)
	case 3200330:
		return FWeaponData{ 4, 1, 4 };  //太刀(金)
	case 3200400:
		return FWeaponData{ 5, 1, 1 };  //阔刀(白)
	case 3200410:
		return FWeaponData{ 5, 1, 2 };  //阔刀(蓝)
	case 3200420:
		return FWeaponData{ 5, 1, 3 };  //阔刀(紫)
	case 3200430:
		return FWeaponData{ 5, 1, 4 };  //阔刀(金)
	case 3201300:
		return FWeaponData{ 6, 2, 1 };  //万刃(白)
	case 3201310:
		return FWeaponData{ 6, 2, 2 };  //万刃(蓝)
	case 3201320:
		return FWeaponData{ 6, 2, 3 };  //万刃(紫)
	case 3201330:
		return FWeaponData{ 6, 2, 4 };  //万刃(金)
	case 3200700:
		return FWeaponData{ 7, 3, 1 };
	case 3200710:
		return FWeaponData{ 7, 3, 2 };
	case 3200720:
		return FWeaponData{ 7, 3, 3 };
	case 3200730:
		return FWeaponData{ 7, 3, 4 };
	case 3200800:
		return FWeaponData{ 8, 3, 1 };
	case 3200810:
		return FWeaponData{ 8, 3, 2 };
	case 3200820:
		return FWeaponData{ 8, 3, 3 };
	case 3200830:
		return FWeaponData{ 8, 3, 4 };
	case 3200900:
		return FWeaponData{ 9, 3, 1 };
	case 3200910:
		return FWeaponData{ 9, 3, 2 };
	case 3200920:
		return FWeaponData{ 9, 3, 3 };
	case 3200930:
		return FWeaponData{ 9, 3, 4 };
	case 3201000:
		return FWeaponData{ 10, 3, 1 };
	case 3201010:
		return FWeaponData{ 10, 3, 2 };
	case 3201020:
		return FWeaponData{ 10, 3, 3 };
	case 3201030:
		return FWeaponData{ 10, 3, 4 };
	case 3201100:
		return FWeaponData{ 11, 3, 1 };
	case 3201110:
		return FWeaponData{ 11, 3, 2 };
	case 3201120:
		return FWeaponData{ 11, 3, 3 };
	case 3201130:
		return FWeaponData{ 11, 3, 4 };
	case 3201200:
		return FWeaponData{ 12, 3, 1 };
	case 3201210:
		return FWeaponData{ 12, 3, 2 };
	case 3201220:
		return FWeaponData{ 12, 3, 3 };
	case 3201230:
		return FWeaponData{ 12, 3, 4 };
	case 3200501:
		return FWeaponData{ 13, 3, 1 };
	case 3200511:
		return FWeaponData{ 13, 3, 2 };
	case 3200521:
		return FWeaponData{ 13, 3, 3 };
	case 3200531:
		return FWeaponData{ 13, 3, 4 };
	}

	return FWeaponData{ NULL, NULL, NULL };
}

FHealthData GetHealthData(ULONG64 PlayerPtr)
{
	INT ActorHealth = ((INT(__fastcall*)(ULONG64))(Module::GameAssembly + ActorHealth_1))(PlayerPtr);

	INT ActorHealthMax = ((INT(__fastcall*)(ULONG64))(Module::GameAssembly + ActorHealthMax_1))(PlayerPtr);

	INT ActorShield = ((INT(__fastcall*)(ULONG64))(Module::GameAssembly + ActorShield_1))(PlayerPtr);

	INT ActorShieldMax = ((INT(__fastcall*)(ULONG64))(Module::GameAssembly + ActorShieldMax_1))(PlayerPtr);

	return FHealthData{ ActorHealth, ActorHealthMax, ActorShield, ActorShieldMax, ActorShieldMax == 500 ? 1 : (ActorShieldMax == 750 ? 2 : (ActorShieldMax == 1000 ? 3 : (ActorShieldMax == 1250 ? 4 : NULL))) };
}

Vector3 GetPlayerPosition(ULONG64 PlayerPtr)
{
	Vector3 Result = Vector3{ 0.f, 0.f, 0.f };

	ULONG64 BackingField = Memory::Read<ULONG64>(PlayerPtr + 0x60);

	if (!Memory::ValidPtr(BackingField))
	{
		ULONG64 CachedPtr = Memory::Read<ULONG64>(BackingField + 0x10);

		if (!Memory::ValidPtr(CachedPtr))
		{
			ULONG64 ActorRootComponent = Memory::Read<ULONG64>(CachedPtr + 0x30);

			if (!Memory::ValidPtr(ActorRootComponent))
			{
				return Memory::Read<Vector3>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(ActorRootComponent + 0x30) + 0x8) + 0x38) + 0x90);
			}
		}
	}

	return Result;
}

VOID WritePlayerPosition(ULONG64 PlayerPtr, Vector3 Position)
{
	ULONG64 BackingField = Memory::Read<ULONG64>(PlayerPtr + 0x60);

	if (!Memory::ValidPtr(BackingField))
	{
		ULONG64 CachedPtr = Memory::Read<ULONG64>(BackingField + 0x10);

		if (!Memory::ValidPtr(CachedPtr))
		{
			ULONG64 ActorRootComponent = Memory::Read<ULONG64>(CachedPtr + 0x30);

			if (!Memory::ValidPtr(ActorRootComponent))
			{
				return Memory::Write<Vector3>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(ActorRootComponent + 0x30) + 0x8) + 0x38) + 0x90, Position);
			}
		}
	}
}

VOID DrawPlayerBox(FLOAT X, FLOAT Y, FLOAT W, FLOAT H, ImVec4 Color, FLOAT Width)
{
	FLOAT _W = FLOAT(W / 4.5f), _H = FLOAT(H / 3.5f);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + _W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + _H), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - _W, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + _H), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + _W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X, Y + H - _H), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - _W, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H), ImVec2(X + W, Y + H - _H), ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Width);
}

VOID DrawPlayerBone(ULONG64 Mesh, ImVec4 Color, FLOAT Width)
{
	Vector3 NeckPosition = GetBonePosition(Mesh, Bone::Neck);

	Vector3 WaistPosition = GetBonePosition(Mesh, Bone::Hips);

	Vector3 previous, current;

	Vector2 p1, c1;

	for (auto a : Bone::BoneList)
	{
		previous = Vector3(0, 0, 0);

		for (int bone : a)
		{
			current = bone == Bone::Neck ? NeckPosition : (bone == Bone::Hips ? WaistPosition : GetBonePosition(Mesh, bone));

			if (previous.x == 0.f)
			{
				previous = current;
				continue;
			}

			p1 = WorldToScreen(previous);

			c1 = WorldToScreen(current);

			Draw::Line(p1.x, p1.y, c1.x, c1.y, Color, Width);

			previous = current;
		}
	}
}

void DrawTransverseHealth(FLOAT x, FLOAT y, FLOAT w, FLOAT h, FLOAT Health, FLOAT MaxHealth, FLOAT Armour, FLOAT MaxArmour)//横向
{
	FLOAT dwDrawWidth, dwDrawWidth2;
	ImColor color = ImColor(255, 0, 0, 255);
	dwDrawWidth = (FLOAT)100 * Health / MaxHealth;
	dwDrawWidth2 = (FLOAT)100 * Armour / MaxArmour;
	if (dwDrawWidth > 20) color = ImColor(255, 165, 0, 255);
	if (dwDrawWidth > 40) color = ImColor(255, 255, 0, 255);
	if (dwDrawWidth > 60) color = ImColor(173, 255, 47, 255);
	if (dwDrawWidth > 80) color = ImColor(0, 255, 0, 255);
	/*
		Draw::FilledRect(x - (MaxHealth - w) / 2, y - 15, 102, 12.0f, ImColor(0, 0, 0, 255));//半透明
		Draw::FilledRect(x - (MaxHealth - w) / 2 + 1, y - 14, dwDrawWidth, 10.0f, color);//当前血量
		Draw::FilledRect(x - (MaxArmour - w) / 2, y - 30, 102, 12.0f, ImColor(0, 0, 0, 255));//半透明
		Draw::FilledRect(x - (MaxArmour - w) / 2 + 1, y - 29, dwDrawWidth2, 10.0f, ImColor(255, 255, 0, 255));//当前血量*/
	CHAR modified[0xFF] = { 0 };
	snprintf(modified, sizeof(modified), "%d / %d\n%d / %d", (DWORD)Health, (DWORD)MaxHealth, (DWORD)Armour, (DWORD)MaxArmour);
	Draw::DrawStrokeText(x + w / 2, y + h + 5, color, modified, 14.f);
}

BOOL DrawItems(ULONG32 ItemID, Vector2 ScreenLocation, FLOAT Distance)
{
	if (ItemID == 3000001 && Menu::物资透视::近武::长剑_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"长剑(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000011 && Menu::物资透视::近武::长剑_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"长剑(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000021 && Menu::物资透视::近武::长剑_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"长剑(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000031 && Menu::物资透视::近武::长剑_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"长剑(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3000100 && Menu::物资透视::近武::匕首_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"匕首(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000110 && Menu::物资透视::近武::匕首_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"匕首(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000120 && Menu::物资透视::近武::匕首_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"匕首(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000130 && Menu::物资透视::近武::匕首_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"匕首(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3000200 && Menu::物资透视::近武::长枪_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"长枪(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000210 && Menu::物资透视::近武::长枪_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"长枪(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000220 && Menu::物资透视::近武::长枪_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"长枪(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000230 && Menu::物资透视::近武::长枪_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"长枪(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3000300 && Menu::物资透视::近武::太刀_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"太刀(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000310 && Menu::物资透视::近武::太刀_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"太刀(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000320 && Menu::物资透视::近武::太刀_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"太刀(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000330 && Menu::物资透视::近武::太刀_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"太刀(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3000400 && Menu::物资透视::近武::阔刀_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"阔刀(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000410 && Menu::物资透视::近武::阔刀_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"阔刀(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000420 && Menu::物资透视::近武::阔刀_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"阔刀(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000430 && Menu::物资透视::近武::阔刀_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"阔刀(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3001300 && Menu::物资透视::近武::万刃轮_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"万刃轮(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001310 && Menu::物资透视::近武::万刃轮_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"万刃轮(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001320 && Menu::物资透视::近武::万刃轮_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"万刃轮(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001330 && Menu::物资透视::近武::万刃轮_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"万刃轮(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3000501 && Menu::物资透视::远武::弓箭_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"弓箭(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000511 && Menu::物资透视::远武::弓箭_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"弓箭(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000521 && Menu::物资透视::远武::弓箭_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"弓箭(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000531 && Menu::物资透视::远武::弓箭_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"弓箭(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3000700 && Menu::物资透视::远武::连弩_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"连弩(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000710 && Menu::物资透视::远武::连弩_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"连弩(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000720 && Menu::物资透视::远武::连弩_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"连弩(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000730 && Menu::物资透视::远武::连弩_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"连弩(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3000800 && Menu::物资透视::远武::火炮_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"火炮(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000810 && Menu::物资透视::远武::火炮_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"火炮(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000820 && Menu::物资透视::远武::火炮_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"火炮(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000830 && Menu::物资透视::远武::火炮_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"火炮(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3001200 && Menu::物资透视::远武::鸟统_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"鸟统(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001210 && Menu::物资透视::远武::鸟统_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"鸟统(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001220 && Menu::物资透视::远武::鸟统_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"鸟统(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001230 && Menu::物资透视::远武::鸟统_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"鸟统(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3001100 && Menu::物资透视::远武::五眼统_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"五眼统(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001110 && Menu::物资透视::远武::五眼统_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"五眼统(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001120 && Menu::物资透视::远武::五眼统_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"五眼统(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001130 && Menu::物资透视::远武::五眼统_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"五眼统(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3000900 && Menu::物资透视::远武::喷火筒_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"喷火筒(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000910 && Menu::物资透视::远武::喷火筒_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"喷火筒(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000920 && Menu::物资透视::远武::喷火筒_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"喷火筒(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3000930 && Menu::物资透视::远武::喷火筒_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"喷火筒(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3001000 && Menu::物资透视::远武::壹蜂窝_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"壹蜂窝(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001010 && Menu::物资透视::远武::壹蜂窝_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"壹蜂窝(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001020 && Menu::物资透视::远武::壹蜂窝_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"壹蜂窝(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3001030 && Menu::物资透视::远武::壹蜂窝_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"壹蜂窝(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3005001 && Menu::物资透视::装备::护甲_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"护甲(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3005002 && Menu::物资透视::装备::护甲_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"护甲(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3005003 && Menu::物资透视::装备::护甲_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"护甲(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3005004 && Menu::物资透视::装备::护甲_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"护甲(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3010018 && Menu::物资透视::消耗::武备匣 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"武备匣(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010020 && Menu::物资透视::消耗::飞索包 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"飞索(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010004 && Menu::物资透视::消耗::小血丸 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"血丸(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010006 && Menu::物资透视::消耗::大血丸 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"血丸(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010023 && Menu::物资透视::消耗::小甲粉 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"甲粉(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010024 && Menu::物资透视::消耗::大甲粉 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"甲粉(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3020010 && Menu::物资透视::属魂::攻击_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"魂·攻击(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020011 && Menu::物资透视::属魂::攻击_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"魂·攻击(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020012 && Menu::物资透视::属魂::攻击_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·攻击(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020013 && Menu::物资透视::属魂::攻击_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"魂·攻击(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3020050 && Menu::物资透视::属魂::近抗_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"魂·近抗(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020051 && Menu::物资透视::属魂::近抗_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"魂·近抗(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020052 && Menu::物资透视::属魂::近抗_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·近抗(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020053 && Menu::物资透视::属魂::近抗_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"魂·近抗(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3020000 && Menu::物资透视::属魂::体力_白 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"魂·体力(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020001 && Menu::物资透视::属魂::体力_蓝 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"魂·体力(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020002 && Menu::物资透视::属魂::体力_紫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·体力(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020003 && Menu::物资透视::属魂::体力_金 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 0.f, 1.f }, 15.f, u8"魂·体力(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3020070 && Menu::物资透视::特魂::妙手 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·妙手(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020071 && Menu::物资透视::特魂::巧匠 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·巧匠(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020073 && Menu::物资透视::特魂::凌波 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·凌波(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020074 && Menu::物资透视::特魂::完璧 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·完璧(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3020075 && Menu::物资透视::特魂::光佑 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·光佑(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020077 && Menu::物资透视::特魂::猫足 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·猫足(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020115 && Menu::物资透视::特魂::财迷 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·财迷(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020114 && Menu::物资透视::特魂::安神 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·安神(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3020079 && Menu::物资透视::特魂::毕工淌 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·毕工淌(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020131 && Menu::物资透视::特魂::吐纳术 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·吐纳术(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020078 && Menu::物资透视::特魂::虚影步 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·虚影步(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020072 && Menu::物资透视::特魂::地堂脚 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·地堂脚(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3020112 && Menu::物资透视::特魂::天赐飞索 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·飞索(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020111 && Menu::物资透视::特魂::天赐武备 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·武备(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020116 && Menu::物资透视::特魂::燃魂一线 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·燃魂一线(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3020124 && Menu::物资透视::特魂::抽芯补天 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"魂·抽芯补天(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3040002 && Menu::物资透视::其他::尸盒 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 0.f, 0.f, 1.f }, 15.f, u8"尸盒(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010008 && Menu::物资透视::其他::刺梨 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"刺梨(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010009 && Menu::物资透视::其他::沙叻 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"沙叻(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010007 && Menu::物资透视::其他::蒲公英 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"蒲公英(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010010 && Menu::物资透视::其他::萤火虫 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 1.f, 1.f, 1.f, 1.f }, 15.f, u8"萤火虫(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010002 && Menu::物资透视::其他::武器扩容 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"武器扩容(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010001 && Menu::物资透视::其他::魂玉扩容 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"魂玉扩容(%.0fm)", Distance);

		return TRUE;
	}
	else if (ItemID == 3010003 && Menu::物资透视::其他::背包扩容 == true)
	{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.f, 1.f, 1.f, 0.85f }, 15.f, u8"背包扩容(%.0fm)", Distance);

		return TRUE;
	}

	else if (ItemID == 3020084 && Menu::物资透视::近魂::噬魂斩 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"噬魂斩(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020085 && Menu::物资透视::近魂::青鬼 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"青鬼(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020086 && Menu::物资透视::近魂::归元 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"归元(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020094 && Menu::物资透视::近魂::太刀 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"太刀(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020088 && Menu::物资透视::近魂::烈火斩 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"烈火斩(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020089 && Menu::物资透视::近魂::破风 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"破风(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020090 && Menu::物资透视::近魂::裂空 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"裂空(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020095 && Menu::物资透视::近魂::阔刀 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"阔刀(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020091 && Menu::物资透视::近魂::凤凰羽 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"凤凰羽(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020092 && Menu::物资透视::近魂::蓝月 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"蓝月(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020093 && Menu::物资透视::近魂::伏天 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"伏天(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020096 && Menu::物资透视::近魂::长剑 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"长剑(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020097 && Menu::物资透视::近魂::空弹 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"空弹(%.0fm)", Distance);

		return TRUE;
		}

	else if (ItemID == 3020098 && Menu::物资透视::远魂::散射 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"散射(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020100 && Menu::物资透视::远魂::羚羊 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"羚羊(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020101 && Menu::物资透视::远魂::爆裂 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"爆裂(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020102 && Menu::物资透视::远魂::速射 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"速射(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020104 && Menu::物资透视::远魂::精准 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"精准(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020105 && Menu::物资透视::远魂::毒箭 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"毒箭(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020106 && Menu::物资透视::远魂::连珠炮 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"连珠炮(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020107 && Menu::物资透视::远魂::反弹 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"反弹(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020108 && Menu::物资透视::远魂::集束 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"集束(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020109 && Menu::物资透视::远魂::落金屋 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"落金屋(%.0fm)", Distance);

		return TRUE;
		}
	else if (ItemID == 3020110 && Menu::物资透视::远魂::甲破 == true)
		{
		Draw::TextEx(ScreenLocation.x, ScreenLocation.y, ImVec4{ 0.909f, 0.f, 1.f, 1.f }, 15.f, u8"甲破(%.0fm)", Distance);

		return TRUE;
		}

	else
	{
		return FALSE;
	}
}

BOOL UpdateBase()
{
	GameData::Base::UWorld = Memory::Read<ULONG64>(Module::GameAssembly + UWorld_1);

	if (!Memory::ValidPtr(GameData::Base::UWorld))
	{
		GameData::Base::Client = Memory::Read<ULONG64>(GameData::Base::UWorld + Client_1);

		if (!Memory::ValidPtr(GameData::Base::Client))
		{
			GameData::Base::Matrix = Memory::Read<ULONG64>(Module::UnityPlayer + Matrix_1);

			if (!Memory::ValidPtr(GameData::Base::Matrix))
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL UpdateLocalPlayer()
{
	GameData::LocalPlayer::Ptr = Memory::Read<ULONG64>(GameData::ActorList::ActorBase + ActorLocalPtr_1);

	if (!Memory::ValidPtr(GameData::LocalPlayer::Ptr))
	{
		GameData::LocalPlayer::State = Memory::Read<ULONG64>(GameData::LocalPlayer::Ptr + ActorState_1);

		if (!Memory::ValidPtr(GameData::LocalPlayer::State))
		{
			GameData::LocalPlayer::ActorKit = Memory::Read<ULONG64>(GameData::LocalPlayer::Ptr + 0xB8);

			if (!Memory::ValidPtr(GameData::LocalPlayer::ActorKit))
			{
				GameData::LocalPlayer::Team = GetPlayerTeam(GameData::LocalPlayer::State);

				//GameData::LocalPlayer::Yaw = get_forward(GameData::LocalPlayer::Ptr);

				GameData::LocalPlayer::Position = GetPlayerPosition(GameData::LocalPlayer::Ptr);

				GameData::LocalPlayer::HealthData = GetHealthData(GameData::LocalPlayer::Ptr);

				GameData::LocalPlayer::WeaponData = GetWeaponData(GameData::LocalPlayer::State);

				GameData::LocalPlayer::BlueSkills = GetAttackSleepTime(GameData::LocalPlayer::Ptr, GameData::LocalPlayer::WeaponData.Id, NULL);

				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL UpdateOtherList()
{
	/*
		if (Module::GameOverlayRenderer != NULL)
		{
			return TRUE;
		}*/
	GameData::Base::EntityManager = Memory::Read<ULONG64>(Module::GameAssembly + EntityManager_1);

	if (!Memory::ValidPtr(GameData::Base::EntityManager))
	{
		GameData::OtherList::OtherBase = Memory::Read<ULONG64>(Memory::Read<ULONG64>(GameData::Base::EntityManager + Client_1));
		{
			if (!Memory::ValidPtr(GameData::OtherList::OtherBase))
			{
				GameData::OtherList::OtherList = Memory::Read<ULONG64>(GameData::OtherList::OtherBase + OtherList_1);

				if (!Memory::ValidPtr(GameData::OtherList::OtherList))
				{
					GameData::OtherList::OtherArray = Memory::Read<ULONG64>(GameData::OtherList::OtherList + OtherArray_1) + OtherArrayStart_1;

					if (!Memory::ValidPtr(GameData::OtherList::OtherArray))
					{
						GameData::OtherList::OtherConut = Memory::Read<ULONG>(GameData::OtherList::OtherList + OtherCountMax_1);

						if (GameData::OtherList::OtherConut > 0 && GameData::OtherList::OtherConut < 1000)
						{
							GameData::DrawOverlay::ItemList.clear();

							return TRUE;
						}
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL UpdateActorList()
{
	GameData::ActorList::ActorBase = Memory::Read<ULONG64>(GameData::Base::Client + ActorBase_1);

	if (!Memory::ValidPtr(GameData::ActorList::ActorBase))
	{
		GameData::ActorList::ActorList = Memory::Read<ULONG64>(GameData::ActorList::ActorBase + ActorList_1);

		if (!Memory::ValidPtr(GameData::ActorList::ActorList))
		{
			GameData::ActorList::ActorInGame = Memory::Read<ULONG>(Memory::Read<ULONG_PTR>(GameData::ActorList::ActorList + 0x10) + 0x18);

			if (GameData::ActorList::ActorInGame != NULL)
			{
				GameData::ActorList::ActorArray = Memory::Read<ULONG64>(GameData::ActorList::ActorList + ActorArray_1) + ActorArrayStart_1;

				if (!Memory::ValidPtr(GameData::ActorList::ActorArray))
				{
					GameData::ActorList::ActorConut = Memory::Read<ULONG>(GameData::ActorList::ActorList + ActorCount_1);

					if (GameData::ActorList::ActorConut > 0 && GameData::ActorList::ActorConut < 100)
					{
						return TRUE;
					}
				}
			}

			if (GameData::ActorList::ActorInGame == NULL)
			{
				ZhenDao::Best::BestPlayerPtr = NULL;

				return FALSE;
			}
		}
	}

	return FALSE;
}

VOID DrawMenu()
{
	if (g_MenuEnable)
	{
		static bool alpha_preview = true;
		static bool alpha_half_preview = true;
		static bool drag_and_drop = true;
		static bool options_menu = true;
		static bool hdr = false;
		ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) |
			(alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

		ImGui::Begin(Menu::菜单设置::g_language == 0 ? (u8"HOME显示/隐藏") : ("HOME Show / Hide"), &g_MenuEnable, ImGuiWindowFlags_NoCollapse);

		ImGui::SetWindowSize({ 550,350 });

		Setlanguage();

		SetESPlayer();

		SetAimPlayer();

		SetFunction();

		ImGui::End();
	}
}

VOID EntityWhile()
{
	if (UpdateBase() && UpdateActorList() && UpdateOtherList() && UpdateLocalPlayer())
	{

		//DbgPrint("EntityWhile");
		if (Menu::预警设置::预警开关::盲区预警 == true)
		{
			Menu::预警设置::预警参数::盲区敌人数量 = 0;

			Menu::预警设置::预警参数::最近距离 = Menu::玩家透视::透视参数::透视有效距离;
		}

		if (Menu::功能设置::功能开关::模拟震刀 == true)
		{
			ZhenDao::Vector::SleepList.clear();

			ZhenDao::Vector::DistanceList.clear();

			ZhenDao::Vector::PlayerPtrList.clear();

		}

		if (Menu::功能设置::功能开关::逆天改命 == true)
		{
			if (GetTickCount64() - BaoMing::TickCount > 1000)
			{
				if (GameData::LocalPlayer::WeaponData.Id != NULL)
				{
					BaoMing::TickCount = GetTickCount64();

					for (ULONG32 i = 0; i < ARRAYSIZE(BaoMing::SavePosition); i++)
					{
						if ((BaoMing::SavePosition[i] - GameData::LocalPlayer::Position).Length() > 50.f)
						{
							BaoMing::SavePosition[i] = GameData::LocalPlayer::Position;

							break;
						}
					}
				}
			}
		}

		if (Menu::功能设置::功能开关::飞龙缠身 == true)
		{
			XiDiRen::Vector::HealthList.clear();

			XiDiRen::Vector::PositionList.clear();
		}

		for (ULONG i = 0; i < GameData::ActorList::ActorConut; i++)
		{
			/*
						auto Rotat = GameData::LocalPlayer::Yaw;
						DbgPrint("Pitch Yaw %.f %.f Roll%.f", Rotat.Pitch, Rotat.Yaw, Rotat.Roll);*/

			ULONG64 ActorPtr = Memory::Read<ULONG64>(GameData::ActorList::ActorArray + (i * 8)); if (Memory::ValidPtr(ActorPtr)) { continue; }

			ULONG64 ActorBase = Memory::Read<ULONG64>(ActorPtr); if (Memory::ValidPtr(ActorBase)) { continue; }

			ULONG64 ActorType = Memory::Read<ULONG64>(ActorBase + 0x20); if (ActorType != PlayerType_1) { continue; }

			ULONG64 ActorState = Memory::Read<ULONG64>(ActorPtr + ActorState_1); if (Memory::ValidPtr(ActorState)) { continue; }

			Vector3 ActorWorldPos = GetPlayerPosition(ActorPtr);

			Vector2 ActorScreenPos = WorldToScreen(ActorWorldPos);

			FLOAT ActorScreenDistance = sqrtf(powf(ActorScreenPos.x - g_d3dViewPort.TopLeftX, 2) + powf(ActorScreenPos.y - g_d3dViewPort.TopLeftY, 2));

			FLOAT ActorWorldDistance = (ActorWorldPos - GameData::LocalPlayer::Position).Length(); if (ActorWorldDistance < 0.f || ActorWorldDistance > 100.f) { continue; }

			ULONG ActorTeam = Memory::Read<ULONG>(ActorState + ActorTeam_1); if (ActorTeam == GameData::LocalPlayer::Team) { continue; }

			ULONG ActorIsBot = Memory::Read<ULONG>(ActorState + ActorIsBot_1);

			FHealthData ActorHealth = GetHealthData(ActorPtr); if (ActorHealth.Health == NULL) { continue; }

			FWeaponData ActorWeapons = GetWeaponData(ActorState);

			Vector3 PlayerHeadWorldPosition = GetBonePosition(ActorPtr, Bone::Head);

			Vector2 PlayerHeadScreenPosition = WorldToScreen(PlayerHeadWorldPosition);

			Vector3 PlayerWaistWorldPosition = GetBonePosition(ActorPtr, Bone::Hips);

			Vector2 PlayerWaistScreenPosition = WorldToScreen(PlayerWaistWorldPosition);

			FLOAT PlayerHeight_1 = PlayerWaistScreenPosition.y - PlayerHeadScreenPosition.y;

			FLOAT PlayerHeight_2 = PlayerHeight_1 / 1.5f;

			FLOAT PlayerHeight_3 = PlayerHeight_1 * 1.5f;

			FLOAT PlayerHeight_4 = PlayerHeight_1 * 3.0f;

			FLOAT PlayerDrawHeight = 0;
			
			if (Menu::预警设置::预警开关::盲区预警 == true)
			{
				if (PlayerHeadScreenPosition.x < 1.0f || PlayerHeadScreenPosition.x > g_d3dViewPort.Width || PlayerHeadScreenPosition.y < 1.0f || PlayerHeadScreenPosition.y > g_d3dViewPort.Height)
				{
					Menu::预警设置::预警参数::盲区敌人数量++;

					if (ActorWorldDistance < Menu::预警设置::预警参数::最近距离)
					{
						Menu::预警设置::预警参数::最近距离 = ActorWorldDistance;
					}

					continue;
				}
			}

			if (Menu::玩家透视::透视开关::显示骨骼 == true)
			{
				DrawPlayerBone(ActorPtr, Menu::玩家瞄准::自瞄参数::m_TargetObject != NULL && Menu::玩家瞄准::自瞄参数::m_TargetObject == ActorPtr ? Menu::全局设置::黄色 : Menu::玩家透视::透视颜色::骨骼颜色, Menu::玩家透视::透视参数::骨骼线条宽度);
			}

			if (Menu::玩家透视::透视开关::显示血量) { DrawTransverseHealth(PlayerWaistScreenPosition.x - PlayerHeight_2, PlayerWaistScreenPosition.y - PlayerHeight_3, PlayerHeight_3, PlayerHeight_4, ActorHealth.Health, ActorHealth.HealthMax, ActorHealth.Shield, ActorHealth.ShieldMax); }

			if (Menu::玩家透视::透视开关::显示方框 == true)
			{
				DrawPlayerBox(PlayerWaistScreenPosition.x - PlayerHeight_2, PlayerWaistScreenPosition.y - PlayerHeight_3, PlayerHeight_3, PlayerHeight_4, Menu::玩家瞄准::自瞄参数::m_TargetObject != NULL && Menu::玩家瞄准::自瞄参数::m_TargetObject == ActorPtr ? Menu::全局设置::红色 : Menu::玩家透视::透视颜色::方框颜色, Menu::玩家透视::透视参数::方框线条宽度);
			}

			if (Menu::玩家透视::透视开关::显示名字 == true)
			{
				LPCWCH PlayerNamePtr = GetPlayerName(ActorState);

				CHAR PlayerName[64] = { 0 };

				WideCharToMultiByte(CP_ACP, 0, PlayerNamePtr, -1, PlayerName, WideCharToMultiByte(CP_ACP, 0, PlayerNamePtr, -1, NULL, 0, NULL, NULL), NULL, NULL);

				PlayerDrawHeight += 20.f;

				//LPCWCH AnimClipNamePtr = GetLastAnimClipName(GameData::LocalPlayer::Ptr);

				//CHAR AnimClipName[260] = { 0 };

				//WideCharToMultiByte(CP_ACP, 0, AnimClipNamePtr, -1, AnimClipName, WideCharToMultiByte(CP_ACP, 0, AnimClipNamePtr, -1, NULL, 0, NULL, NULL), NULL, NULL);

				//DbgPrint("%s %llX %s %d", PlayerName, ActorPtr, AnimClipName, GetPlayerAttack(GameData::LocalPlayer::Ptr));

				Draw::TextEx(PlayerHeadScreenPosition.x + PlayerHeight_2, PlayerHeadScreenPosition.y + PlayerDrawHeight, Menu::玩家透视::透视颜色::名字颜色, 15.f, u8"%s(%d)", ActorIsBot != NULL ? u8"人机电脑" : Draw::AnsiToUTF8(PlayerName).c_str(), ActorTeam);
			}

			if (Menu::玩家透视::透视开关::显示装备 == true)
			{
				static char* ArmorNames[] = {
					u8"裸屌",
					u8"白甲",
					u8"蓝甲",
					u8"紫甲",
					u8"金甲"
				};

				static char* WeaponNames[] = {
					u8"赤手空拳",
					u8"长剑",
					u8"匕首",
					u8"长枪",
					u8"太刀",
					u8"阔刀",
					u8"万刃轮",
					u8"连弩",
					u8"火炮",
					u8"喷火筒",
					u8"壹蜂窝",
					u8"五眼统",
					u8"鸟统",
					u8"弓箭"
				};

				static ImVec4 EquipmentColors[] = {
					ImVec4{ 1.f, 1.f, 1.f, 1.f },
					ImVec4{ 1.f, 1.f, 1.f, 1.f },
					ImVec4{ 0.f, 1.f, 1.f, 0.85f },
					ImVec4{ 0.909f, 0.f, 1.f, 1.f },
					ImVec4{ 1.f, 1.f, 0.f, 1.f }
				};

				PlayerDrawHeight += 20.f;

				Draw::TextEx(PlayerHeadScreenPosition.x + PlayerHeight_2 + 0.0f, PlayerHeadScreenPosition.y + PlayerDrawHeight, EquipmentColors[ActorHealth.ShieldType], 15.f, u8"%s", ArmorNames[ActorHealth.ShieldType]);

				Draw::TextEx(PlayerHeadScreenPosition.x + PlayerHeight_2 + 28.f, PlayerHeadScreenPosition.y + PlayerDrawHeight, ImVec4{ 0.75f, 0.75f, 0.75f, 0.75f }, 15.f, "/");

				Draw::TextEx(PlayerHeadScreenPosition.x + PlayerHeight_2 + 40.f, PlayerHeadScreenPosition.y + PlayerDrawHeight, EquipmentColors[ActorWeapons.Color], 15.f, u8"%s", WeaponNames[ActorWeapons.Id]);
			}

			if (Menu::玩家透视::透视开关::显示名字 == true)
			{
				PlayerDrawHeight += 20.f;

				Draw::TextEx(PlayerHeadScreenPosition.x + PlayerHeight_2, PlayerHeadScreenPosition.y + PlayerDrawHeight, Menu::玩家透视::透视颜色::距离颜色, 15.f, u8"%0.fm", ActorWorldDistance);
			}

			if (Menu::玩家透视::透视开关::显示射线 == true)
			{
				Draw::Line(g_d3dViewPort.TopLeftX, g_d3dViewPort.Height, PlayerWaistScreenPosition.x, PlayerWaistScreenPosition.y, Menu::玩家瞄准::自瞄参数::m_TargetObject != NULL && Menu::玩家瞄准::自瞄参数::m_TargetObject == ActorPtr ? Menu::全局设置::红色 : Menu::玩家透视::透视颜色::射线颜色, Menu::玩家透视::透视参数::射线线条宽度);
			}

			if (Menu::玩家瞄准::自瞄开关::内存自瞄 == true)
			{
				Vector3 AimPos = GetBonePosition(ActorPtr, Menu::玩家瞄准::自瞄开关::自瞄位置);
				if (WorldToScreen(&AimPos))
				{
					if (Menu::玩家瞄准::自瞄参数::m_Lock == FALSE)
					{
						Menu::玩家瞄准::自瞄参数::Value = TakeCollimatedDistance(g_d3dViewPort.Width * 0.5f, g_d3dViewPort.Height * 0.5f, AimPos.x, AimPos.y);
						if (Menu::玩家瞄准::自瞄参数::Value < Menu::玩家瞄准::自瞄参数::m_Size)
						{
							if (Menu::玩家瞄准::自瞄参数::RecentValue == NULL)
							{
								Menu::玩家瞄准::自瞄参数::RecentValue = Menu::玩家瞄准::自瞄参数::Value;
								Menu::玩家瞄准::自瞄参数::m_TargetObject = ActorPtr;
							}
							else if (Menu::玩家瞄准::自瞄参数::Value < Menu::玩家瞄准::自瞄参数::RecentValue)
							{
								Menu::玩家瞄准::自瞄参数::RecentValue = Menu::玩家瞄准::自瞄参数::Value;
								Menu::玩家瞄准::自瞄参数::m_TargetObject = ActorPtr;
							}
						}
					}

				}
			}

			if (Menu::功能设置::功能开关::模拟震刀 == true)
			{
				if (GameData::LocalPlayer::WeaponData.Type == 1 && ActorWeapons.Type == 1 && GetPlayerAttack(ActorPtr) == 1)
				{
					if (ActorWorldDistance < 8.f)
					{
						DWORD SleepTime = GetAttackSleepTime(ActorPtr, ActorWeapons.Id, ActorWorldDistance);
						//DbgPrint("%d", SleepTime);
						if (SleepTime != 0 && SleepTime != 9999)
						{
							ZhenDao::Vector::SleepList.push_back(SleepTime);

							ZhenDao::Vector::DistanceList.push_back(ActorWorldDistance);

							ZhenDao::Vector::PlayerPtrList.push_back(ActorPtr);
						}
					}
				}
			}

			if (Menu::功能设置::功能开关::飞龙缠身 == true)
			{
				if (GameData::LocalPlayer::WeaponData.Type == 1)
				{
					DWORD SleepTime = GetAttackSleepTime(ActorPtr, ActorWeapons.Id, ActorWorldDistance);

					if (GameData::LocalPlayer::BlueSkills != 0 && GameData::LocalPlayer::BlueSkills != 9999 && SleepTime != 9999)
					{
						if (ActorWorldDistance > 2.5f && ActorWorldDistance < 12.5f)
						{
							XiDiRen::Vector::PositionList.push_back(ActorWorldPos);

							XiDiRen::Vector::HealthList.push_back(ActorHealth.Health + ActorHealth.Shield);
						}
					}
				}
			}
		}

		for (ULONG i = 0; i < GameData::OtherList::OtherConut; i++)
		{
			ULONG64 EntityPtr = Memory::Read<ULONG64>(GameData::OtherList::OtherArray + (i * 16)); if (Memory::ValidPtr(EntityPtr)) { continue; }

			ULONG64 EntityBase = Memory::Read<ULONG64>(EntityPtr); if (Memory::ValidPtr(EntityBase)) { continue; }

			ULONG64 EntityType = Memory::Read<ULONG64>(EntityBase + 0x20); if (EntityType != ItemDropType_1) { continue; }

			ULONG64 EntityId = Memory::Read<ULONG>(Memory::Read<ULONG64>(EntityPtr + 0x58) + 0x30); if (EntityId == NULL) { continue; }

			ULONG64 EntityDropItem = Memory::Read<ULONG64>(EntityPtr + OtherEntDropItem_1); if (Memory::ValidPtr(EntityDropItem)) { continue; }

			ULONG64 EntityTransformData = UnityEngine::GetOtherTransform(EntityDropItem); if (Memory::ValidPtr(EntityTransformData)) { continue; }

			Vector3 EntityWorldPos = UnityEngine::TransformToWorld(EntityTransformData);

			Vector2 EntityScreenPos = WorldToScreen(EntityWorldPos);

			FLOAT EntityWorldDistance = (EntityWorldPos - GameData::LocalPlayer::Position).Length(); if (EntityWorldDistance < 0.f || EntityWorldDistance > 100.f) { continue; }

			for (ULONG iii = 0; iii < GameData::DrawOverlay::ItemList.size(); iii++)
			{
				if (EntityScreenPos.x > GameData::DrawOverlay::ItemList[iii].x - 80.f && EntityScreenPos.x < GameData::DrawOverlay::ItemList[iii].x + 80.f && EntityScreenPos.y > GameData::DrawOverlay::ItemList[iii].y - 15.f && EntityScreenPos.y < GameData::DrawOverlay::ItemList[iii].y + 15.f)
				{
					EntityScreenPos = GameData::DrawOverlay::ItemList[iii];

					EntityScreenPos.y = EntityScreenPos.y - 15.f * 0.85f;
				}
			}

			if (DrawItems(EntityId, EntityScreenPos, EntityWorldDistance))
			{
				GameData::DrawOverlay::ItemList.push_back(EntityScreenPos);
			}
		}

		if (Menu::玩家瞄准::自瞄开关::内存自瞄 == true)
		{
			if (Menu::玩家瞄准::自瞄开关::范围开关) { Draw::DrawCircle(g_d3dViewPort.Width * 0.5F, g_d3dViewPort.Height * 0.5F, Menu::玩家瞄准::自瞄参数::m_Size, Menu::全局设置::白色, Menu::玩家瞄准::自瞄参数::m_Size, 1.f); }

			if (Menu::玩家瞄准::自瞄参数::m_TargetObject > NULL)
			{
				Vector3 AimPos = GetBonePosition(Menu::玩家瞄准::自瞄参数::m_TargetObject, Menu::玩家瞄准::自瞄开关::自瞄位置);
				AimPos.z += 0.12f;
				if (GetAsyncKeyState(Menu::玩家瞄准::自瞄开关::自瞄热键) != NULL)
				{
					Menu::玩家瞄准::自瞄参数::m_Lock = TRUE;
					FHealthData AimHealth = GetHealthData(Menu::玩家瞄准::自瞄参数::m_TargetObject);
					auto actorWeapon = Memory::Read<uintptr_t>(GameData::LocalPlayer::Ptr + 0xE0);
					auto weaponType = Memory::Read<DWORD>(actorWeapon + 0x60);

					auto PredPos = aimbot::GetPrediction(Menu::玩家瞄准::自瞄参数::m_TargetObject, AimPos, GameData::LocalPlayer::Position, weaponType);
					if (AimHealth.Health != NULL)
					{
						if (WorldToScreen(&PredPos))//AimPos
						{
							MouseAimBot(PredPos, TRUE);//AimPos
						}
					}
					else
					{
						Menu::玩家瞄准::自瞄参数::m_Lock = FALSE;
						Menu::玩家瞄准::自瞄参数::m_TargetObject = NULL;
						Menu::玩家瞄准::自瞄参数::RecentValue = 0.F;
					}
				}
				else
				{
					Menu::玩家瞄准::自瞄参数::m_Lock = FALSE;
					Menu::玩家瞄准::自瞄参数::m_TargetObject = NULL;
					Menu::玩家瞄准::自瞄参数::RecentValue = 0.F;
				}
			}
		}

		if (Menu::玩家透视::透视开关::显示准心 == true)
		{
			Draw::Line(g_d3dViewPort.TopLeftX - Menu::玩家透视::透视参数::准心尺寸调节, g_d3dViewPort.TopLeftY, g_d3dViewPort.TopLeftX + Menu::玩家透视::透视参数::准心尺寸调节, g_d3dViewPort.TopLeftY, Menu::玩家透视::透视颜色::准心颜色, Menu::玩家透视::透视参数::准心线条宽度);

			Draw::Line(g_d3dViewPort.TopLeftX, g_d3dViewPort.TopLeftY - Menu::玩家透视::透视参数::准心尺寸调节, g_d3dViewPort.TopLeftX, g_d3dViewPort.TopLeftY + Menu::玩家透视::透视参数::准心尺寸调节, Menu::玩家透视::透视颜色::准心颜色, Menu::玩家透视::透视参数::准心线条宽度);
		}

		if (Menu::预警设置::预警开关::盲区预警 == true)
		{
			if (Menu::预警设置::预警参数::最近距离 > 5.f && Menu::预警设置::预警参数::盲区敌人数量 > 0)
			{
				Draw::TextEx(g_d3dViewPort.TopLeftX - 195.f, g_d3dViewPort.Height / 5.5f, Menu::预警设置::预警参数::最近距离 > Menu::玩家透视::透视参数::透视有效距离 / 1.5 ? Menu::预警设置::预警颜色::盲区远距预警颜色 : (Menu::预警设置::预警参数::最近距离 > Menu::玩家透视::透视参数::透视有效距离 / 3 ? Menu::预警设置::预警颜色::盲区中距预警颜色 : Menu::预警设置::预警颜色::盲区近距预警颜色), 24.f, u8"盲区内共有 %d 名敌人，距您最近的敌人 %.1f 米", Menu::预警设置::预警参数::盲区敌人数量, Menu::预警设置::预警参数::最近距离);
			}
		}

		if (Menu::功能设置::功能开关::模拟震刀 == true)
		{
			ULONG MinIndex = NULL;

			SIZE_T ListLen = ZhenDao::Vector::DistanceList.size();

			if (ListLen > 0)
			{
				FLOAT MinDistance = ZhenDao::Vector::DistanceList[0];

				for (ULONG ListIndex = 1; ListIndex < ListLen; ListIndex++)
				{
					if (ZhenDao::Vector::DistanceList[ListIndex] < MinDistance)
					{
						MinDistance = ZhenDao::Vector::DistanceList[ListIndex];

						MinIndex = ListIndex;
					}
				}

				ZhenDao::Best::BestSleepTime = ZhenDao::Vector::SleepList[MinIndex];

				ZhenDao::Best::BestPlayerPtr = ZhenDao::Vector::PlayerPtrList[MinIndex];

				ZhenDao::Best::BestPlayerDistance = ZhenDao::Vector::DistanceList[MinIndex];
			}
			else
				ZhenDao::Best::BestPlayerPtr = NULL;
		}

		if (Menu::功能设置::功能开关::凌波微步 == true)
		{
			ULONG64 RuntimePropertyData = Memory::Read<ULONG64>(GameData::LocalPlayer::Ptr + 0x90);

			if (!Memory::ValidPtr(RuntimePropertyData))
			{
				ULONG64 RuntimeBattlePropDic = Memory::Read<ULONG64>(RuntimePropertyData + 0x10);

				if (!Memory::ValidPtr(RuntimeBattlePropDic))
				{
					ULONG64 ListNoGC = Memory::Read<ULONG64>(RuntimeBattlePropDic + 0x28);

					if (!Memory::ValidPtr(ListNoGC))
					{
						*(ULONG64*)(*(ULONG64*)(ListNoGC + 0x10) + 0x20) = *(ULONG64*)(*(ULONG64*)(ListNoGC + 0x10) + 0x28);
					}
				}
			}
		}

		if (Menu::功能设置::功能开关::逆天改命 == true)
		{
			if (GameData::LocalPlayer::HealthData.Shield + GameData::LocalPlayer::HealthData.Health > 0 && GameData::LocalPlayer::HealthData.Shield + GameData::LocalPlayer::HealthData.Health < 500)
			{
				if (Menu::预警设置::预警参数::最近距离 < 15.f)
				{
					for (ULONG32 i = 0; i < ARRAYSIZE(BaoMing::SavePosition); i++)
					{
						if ((BaoMing::SavePosition[i] - GameData::LocalPlayer::Position).Length() > 35.f && (BaoMing::SavePosition[i] - GameData::LocalPlayer::Position).Length() < 50.f)
						{
							WritePlayerPosition(GameData::LocalPlayer::Ptr, BaoMing::SavePosition[i]);

							break;
						}
					}
				}
			}
		}

		if (Menu::功能设置::功能开关::飞龙缠身 == true)
		{
			if (GameData::LocalPlayer::HealthData.Shield + GameData::LocalPlayer::HealthData.Health > 500)
			{
				ULONG MinIndex = NULL;

				SIZE_T ListLen = XiDiRen::Vector::HealthList.size();

				if (ListLen > 0)
				{
					FLOAT MinDistance = XiDiRen::Vector::HealthList[0];

					for (ULONG ListIndex = 1; ListIndex < ListLen; ListIndex++)
					{
						if (XiDiRen::Vector::HealthList[ListIndex] < MinDistance)
						{
							MinDistance = XiDiRen::Vector::HealthList[ListIndex];

							MinIndex = ListIndex;
						}
					}

					WritePlayerPosition(GameData::LocalPlayer::Ptr, XiDiRen::Vector::PositionList[MinIndex]);
				}
			}
		}
	}
}

HRESULT WINAPI NewPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (ImGui_ImplDX11_Init(pSwapChain) && ImGui_ImplWin32_Init())
	{
		Menustyler();
		Menucolor();
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		DrawMenu();
		EntityWhile();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return Memory::CALL<HRESULT>(Draw::OldPresent, pSwapChain, SyncInterval, Flags);
}

//void Consloe()
//{
//	AllocConsole();
//	freopen("CON", "w", stdout);
//	CONSOLE_SCREEN_BUFFER_INFO Info = { 0 };
//	memset(&Info, 0, sizeof(Info));
//	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
//}

VOID StartThread()
{
	//Consloe();
	do
	{
		Sleep(0);
		Module::GameBase = (uintptr_t)GetModuleHandleA(NULL);
	} while (!Module::GameBase);

	do
	{
		Sleep(0);
		Module::UnityPlayer = (ULONG64)GetModuleHandleA("UnityPlayer.dll");
	} while (!Module::UnityPlayer);

	do
	{
		Sleep(0);
		Module::GameAssembly = (ULONG64)GetModuleHandleA("GameAssembly.dll");
	} while (!Module::GameAssembly);


	Module::GameOverlayRenderer = (uintptr_t)GetModuleHandleA(TEXT("GameOverlayRenderer64.dll"));

	if (Module::GameOverlayRenderer)
	{
		do
		{
			if (Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Module::GameOverlayRenderer + 0x1BACA8) + 0xF0)) != NULL)//0x1B9CA8
			{
				static unsigned long long Table[1000] = { 0 };

				Memory::RtlCopyMemoryEx((PBYTE)&Table, (PBYTE)Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Module::GameOverlayRenderer + 0x1BACA8) + 0xF0)), sizeof(Table));

				Draw::OldPresent = Memory::Read<uintptr_t>((uintptr_t)&Table + 0x40);

				Memory::Write<uintptr_t>((uintptr_t)&Table + 0x40, (uintptr_t)NewPresent);

				Memory::Write<uintptr_t>(Memory::Read<uintptr_t>(Memory::Read<uintptr_t>(Module::GameOverlayRenderer + 0x1BACA8) + 0xF0), (uintptr_t)&Table);

				GSInject::DeleteInject();

				break;
			}
			else
				Sleep(0);
		} while (true);
	}
	else
	{
		do
		{
			if (Memory::Read<ULONG64>(Module::UnityPlayer + VTableAddr) != NULL &&
				Memory::Read<ULONG64>(Memory::Read<ULONG64>(Module::UnityPlayer + VTableAddr) + VTable_1) != NULL &&
				Memory::Read<ULONG64>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(Module::UnityPlayer + VTableAddr) + VTable_1)) != NULL &&
				Memory::Read<ULONG64>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(Module::UnityPlayer + VTableAddr) + VTable_1)) + 0x40) != NULL)
			{
				static unsigned char Table[1000] = { 0 };

				Memory::RtlCopyMemoryEx((PBYTE)&Table, Memory::Read<PBYTE>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(Module::UnityPlayer + VTableAddr) + VTable_1)), sizeof(Table));

				Draw::OldPresent = Memory::Read<ULONG64>((ULONG64)&Table + 0x40);

				Memory::Write<ULONG64>((ULONG64)&Table + 0x40, (ULONG64)NewPresent);

				Memory::Write<ULONG64>(Memory::Read<ULONG64>(Memory::Read<ULONG64>(Module::UnityPlayer + VTableAddr) + VTable_1), (ULONG64)&Table);

				GSInject::DeleteInject();
				break;
			}
			else
				Sleep(1000);
		} while (true);
	}

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		Memory::RtlZeroMemoryEx((BYTE*)hModule, 0x1000);

		StartThread();
	}

	return TRUE;
}