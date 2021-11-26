#pragma once
#define VTableAddr 0x18507E8
#define VTable_1 0x3A0
#define UWorld_1 0x725D718  
#define EntityManager_1 0x717A290  //
#define Client_1 0xB8 // 

#define Matrix_1 0x186C110 // 
#define Matrix_2 0x1A8 // 
#define Matrix_3 0xDC //

#define ActorBase_1	0x08
#define ActorList_1	0x60//
#define ActorArray_1 0x10
#define ActorCount_1 0x18
#define ActorLocalPtr_1 0x18
#define ActorArrayStart_1 0x20
#define OtherList_1 0x28
#define OtherArray_1 0x18
#define OtherCount_1 0x20
#define OtherCountMax_1 0x24
#define OtherArrayStart_1 0x28
#define OtherEntDropItem_1 0xB0//
#define PlayerType_1 0x33C7
#define ItemDropType_1 0x4B8C
#define ActorState_1 0x238//
#define ActorTeam_1 0xC0
#define ActorIsBot_1 0xDC
#define ActorState_WeaponId_1 0xD4
#define ZhenDaoMessage_1 0x1E240


#define ActorHealth_1 0x71B770 // 
#define ActorHealthMax_1 0x71B6F0 // 
#define ActorShield_1 0x71CA50  // 
#define ActorShieldMax_1 0x71C9B0 

#define UnityEngine_TransformToWorld_1 0x4105C80 // 
#define UnityEngine_GetBoneTransform_1 0x4A79FE0 // U
#define UnityEngine_GetOtherTransform_1 0x408F1E0 // 

#define TryToEmptyStep_1 0x90EFB0 //
#define CrossFadeDinnerDodge_1 0x909CC0  // 

#define m_Setforward 0x4106210//
#define m_Getforward 0x41055C0//

#define m_HeavyDown 0x30936E0//
#define m_HeavyPress 0x30937F0//
#define m_HeavyUp 0x3093880//
#define m_LightDown 0x3093420//
#define m_LightPress 0x3093560 //
#define m_LightUp 0x30935F0//
#define m_JumpDown 0x3094380//
#define m_JumpHold 0x30944A0//
#define m_JumpUP 0x3094550//
#define m_CrouchDown 0x3093910//
#define m_CrouchUP 0x30939C0
#define m_DodgeDown 0x3093A70
#define m_DodgePress 0x3093B20//
#define m_DodgeUp 0x3093B60//



#define m_GameUpdate 0xA93BE0

#define SendAttackCache  0x929BE0
#define c_CacheHook 0x346ECFE
#define c_CacheBack  c_CacheHook + 6

#define m_GetVelocity 0x4A7AC80 //更新//预判自瞄更新地址

extern "C" uintptr_t WINAPI DOGE_CACHE_ATTACK();

enum WeaponId
{
	长剑 = 1,
	匕首 = 2,
	长枪 = 3,
	太刀 = 4,
	阔刀 = 5,
};

struct Vector2
{
public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}

	float x;
	float y;

	Vector2 operator+(Vector2 v)
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(Vector2 v)
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator*(float v)
	{
		return Vector2(x * v, y * v);
	}

	Vector2 operator/(float v)
	{
		return Vector2(x / v, y / v);
	}
};

struct Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f) {}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float x;
	float y;
	float z;

	inline Vector3 ToFRotator()
	{
		float RADPI = (float)(180 / 3.1415926f);
		float Yaw = (float)atan2f(y, x) * RADPI;
		float Pitch = (float)atan2f(z, sqrtf(powf(x, 2) + powf(y, 2))) * RADPI;
		float Roll = 0;
		return Vector3(Pitch, Yaw, Roll);
	}

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2) + powf(v.y - y, 2) + powf(v.z - z, 2)));
	}

	inline float Length()
	{
		return float(sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2)));
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(Vector3 v)
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	Vector3 operator/(Vector3 v)
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}
};

struct Vector4
{
public:
	Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}

	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

	float x;
	float y;
	float z;
	float w;
};



struct FRotator
{
public:
	FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f) {}

	FRotator(float _pitch, float _yaw, float _roll) : Pitch(_pitch), Yaw(_yaw), Roll(_roll) {}

	~FRotator() {}

	float Pitch;
	float Yaw;
	float Roll;

	inline double Length()
	{
		return sqrtf(powf(Pitch, 2.0) + powf(Yaw, 2.0) + powf(Roll, 2.0));
	};

	void Clamp()
	{
		if (Pitch > 180)
			Pitch -= 360;

		else if (Pitch < -180)
			Pitch += 360;

		if (Yaw > 180)
			Yaw -= 360;

		else if (Yaw < -180)
			Yaw += 360;

		if (Pitch < -89)
			Pitch = -89;

		if (Pitch > 89)
			Pitch = 89;

		while (Yaw < -180.0f)
			Yaw += 360.0f;

		while (Yaw > 180.0f)
			Yaw -= 360.0f;

		Roll = 0;
		return;
	}


	Vector3 ToVector()
	{
		float radPitch = (float)(Pitch * 3.1415926f / 180.f);
		float radYaw = (float)(Yaw * 3.1415926f / 180.f);

		float SP = (float)sinf(radPitch);
		float CP = (float)cosf(radPitch);
		float SY = (float)sinf(radYaw);
		float CY = (float)cosf(radYaw);

		return  Vector3(CP * CY, CP * SY, SP);
	}

	D3DMATRIX GetAxes()
	{
		auto tempMatrix = Matrix();
		return tempMatrix;
	}

	D3DMATRIX Matrix(Vector3 origin = Vector3(0, 0, 0))
	{
		float radPitch = (Pitch * 3.1415926f / 180.f);
		float radYaw = (Yaw * 3.1415926f / 180.f);
		float radRoll = (Roll * 3.1415926f / 180.f);
		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		D3DMATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}

	FRotator operator+(FRotator v)
	{
		return FRotator(Pitch + v.Pitch, Yaw + v.Yaw, Roll + v.Roll);
	}

	FRotator operator-(FRotator v)
	{
		return FRotator(Pitch - v.Pitch, Yaw - v.Yaw, Roll - v.Roll);
	}

	FRotator operator*(FRotator v)
	{
		return FRotator(Pitch * v.Pitch, Yaw * v.Yaw, Roll * v.Roll);
	}

	FRotator operator/(FRotator v)
	{
		return FRotator(Pitch / v.Pitch, Yaw / v.Yaw, Roll / v.Roll);
	}
};

struct FItemData
{
	INT Id;
	INT Type;
	INT Color;
};

struct FWeaponData
{
	INT Id;
	INT Type;
	INT Color;
};

struct FHealthData
{
	INT Health;
	INT HealthMax;
	INT Shield;
	INT ShieldMax;
	INT ShieldType;
};
struct TEXTPlus
{
	char Str[128];
};
