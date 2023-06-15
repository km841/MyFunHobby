#pragma once

#define _HAS_STD_BYTE 0 

#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <functional>
#include <mutex>
#include <queue>
#include <type_traits>
#include <optional>
#include <bitset>
#include <numeric>

#include <filesystem>
namespace fs = std::filesystem;

#include "d3d11.h"
#include "SimpleMath.h"
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>

#include <PhysX/PxPhysicsAPI.h>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")

#pragma comment(lib, "PhysX\\debug\\PhysX_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXFoundation_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXCommon_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXExtensions_static_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXPvdSDK_static_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXCharacterKinematic_static_64.lib")

#pragma comment(lib, "FW1FontWrapper\\FW1FontWrapper.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")

#pragma comment(lib, "PhysX\\release\\PhysX_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXFoundation_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXCommon_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXExtensions_static_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXPvdSDK_static_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXCharacterKinematic_static_64.lib")
#endif

using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;
using namespace physx;

#include "FilterShaders.h"
#include "ReportCallback.h"
#include "Common.h"
#include "EnumDefine.h"


// 각종 lib
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

// 각종 typedef

using Vec2 = DirectX::SimpleMath::Vector2;
using Vec3 = DirectX::SimpleMath::Vector3;
using Vec4 = DirectX::SimpleMath::Vector4;
using Matrix = DirectX::SimpleMath::Matrix;

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;

using std::string;
using std::wstring;
using std::weak_ptr;

using std::static_pointer_cast;
using std::dynamic_pointer_cast;

using RaycastResult = std::pair<bool, Vec3>;


#include "ObjectInfo.h"

struct Color
{
	uint32 iValue;

	static Color FromRGB(uint8 iRed, uint8 iGreen, uint8 iBlue, float fAlpha = 1.f) 
	{
		uint8 iAlpha = static_cast<uint8>(255.f * fAlpha);
		return Color{ static_cast<uint32>((iAlpha << 24) | (iBlue << 16) | (iGreen << 8) | iRed)  };
	};

	operator uint32()		{ return iValue; }
	operator uint32() const { return iValue; }
};

struct WindowInfo
{
	HWND hHwnd;
	int32 iWidth;
	int32 iHeight;
	bool bWindowed;
};


struct Vertex
{
	Vertex() {}
	Vertex(Vec3 vPos, Vec2 vUV, Vec3 vNormal)
		: vPos(vPos), vUV(vUV), vNormal(vNormal)
	{}

	Vec3 vPos;
	Vec2 vUV;
	Vec3 vNormal;

public:


	static std::vector<Vertex> CreateBoxVertices(Vec3 vBoxHalfSize)
	{
		std::vector<Vertex> vVertices;

		vVertices.push_back({ Vec3(-vBoxHalfSize.x, vBoxHalfSize.y, 0.f), Vec2(0.f, 0.f), Vec3(0.f, 0.f, -1.f)});
		vVertices.push_back({ Vec3(vBoxHalfSize.x, vBoxHalfSize.y, 0.f), Vec2(1.f, 0.f), Vec3(0.f, 0.f, -1.f) });
		vVertices.push_back({ Vec3(vBoxHalfSize.x, -vBoxHalfSize.y, 0.f), Vec2(1.f, 1.f), Vec3(0.f, 0.f, -1.f) });
		vVertices.push_back({ Vec3(-vBoxHalfSize.x, -vBoxHalfSize.y, 0.f), Vec2(0.f, 1.f), Vec3(0.f, 0.f, -1.f) });

		return vVertices;
	}

	static std::pair<std::vector<Vertex>, std::vector<uint32>> CreateBoxVerticesAndIndices(Vec3 vBoxHalfSize)
	{
		std::vector<Vertex> vVertices = CreateBoxVertices(vBoxHalfSize);
		std::vector<uint32> vIndices;

		vIndices.push_back(0);
		vIndices.push_back(1);
		vIndices.push_back(2);
		vIndices.push_back(3);
		vIndices.push_back(0);

		return make_pair(vVertices, vIndices);
	}

	static std::pair<std::vector<Vertex>, std::vector<uint32>> CreateBoxVerticesAndIndicesTri(Vec3 vBoxHalfSize)
	{
		std::vector<Vertex> vVertices = CreateBoxVertices(vBoxHalfSize);
		std::vector<uint32> vIndices;

		vIndices.push_back(0);
		vIndices.push_back(1);
		vIndices.push_back(2);

		vIndices.push_back(0);
		vIndices.push_back(2);
		vIndices.push_back(3);

		return make_pair(vVertices, vIndices);
	}

	// 미구현
	static std::pair<std::vector<Vertex>, std::vector<uint32>> CreateCapsuleVerticesAndIndices(float fRadius, float fHeight, float fSlices)
	{
		std::vector<Vertex> vVertices;
		std::vector<uint32> vIndices;

		return make_pair(vVertices, vIndices);
	}
};

struct TransformParams
{
	Matrix matOldWorld;
	Matrix matOldView;
	Matrix matOldWV;

	Matrix matWorld;
	Matrix matView;
	Matrix matProjection;
	Matrix matWV;
	Matrix matWVP;
	Matrix matWVPInv;
};

enum
{
	MATERIAL_VALUE_COUNT = 4,
};


struct MaterialParams
{
	MaterialParams()
	{
		memset(this, 0, sizeof(MaterialParams));
	}

	std::array<uint32, MATERIAL_VALUE_COUNT> arrIntParams;
	std::array<float, MATERIAL_VALUE_COUNT> arrFloatParams;
	std::array<uint32, MATERIAL_VALUE_COUNT> arrTexOnParams;
	std::array<Vec2, MATERIAL_VALUE_COUNT> arrVec2Params;
	std::array<Vec3, MATERIAL_VALUE_COUNT> arrVec3Params;
	std::array<Vec4, MATERIAL_VALUE_COUNT> arrVec4Params;

	void SetInt(uint8 iIndex, int32 iValue) { arrIntParams[iIndex] = iValue; }
	void SetFloat(uint8 iIndex, float fValue) { arrFloatParams[iIndex] = fValue; }
	void SetTexOn(uint8 iIndex, int32 iValue) { arrTexOnParams[iIndex] = iValue; }
	void SetVec2(uint8 iIndex, Vec2 vValue) { arrVec2Params[iIndex] = vValue; }
	void SetVec3(uint8 iIndex, Vec3 vValue) { arrVec3Params[iIndex] = vValue; }
	void SetVec4(uint8 iIndex, Vec4 vValue) { arrVec4Params[iIndex] = vValue; }
};

struct Status
{
	Status()
		: iMaxHP(0)
		, iCurHP(0)
		, iAttack(0)
		, iShield(0)
		, iDefence(0)
		, fSpeed(0)
		, bAlive(true)
		, fAttackDist(0.f)
		, fRecogDist(0.f)
		, fCriticalPercent(0.f)
	{}

	void PlayerDefaultSetting()
	{
		iMaxHP = 100;
		iCurHP = 100;
		iShield = 0;
		iAttack = 1;
		iDefence = 1;
		fSpeed = 400.f;
		bAlive = true;
		fCriticalPercent = 30.f;
	}

	void MonsterDefaultSetting()
	{
		iMaxHP = 10;
		iCurHP = 10;
		iShield = 0;
		iAttack = 1;
		iDefence = 1;
		fSpeed = 200.f;
		bAlive = true;
		fRecogDist = 100.f;
		fAttackDist = 50.f;
	}

	void KnightMonsterDefaultSetting()
	{
		iMaxHP = 20;
		iCurHP = 20;
		iShield = 0;
		iAttack = 1;
		iDefence = 1;
		fSpeed = 200.f;
		bAlive = true;
		fRecogDist = 300.f;
		fAttackDist = 100.f;
	}

	void AlchemistMonsterDefaultSetting()
	{
		iMaxHP = 20;
		iCurHP = 20;
		iShield = 0;
		iAttack = 1;
		iDefence = 1;
		fSpeed = 150.f;
		bAlive = true;
		fRecogDist = 300.f;
		fAttackDist = 100.f;
	}

	void ErodedKnightMonsterDefaultSetting()
	{
		iMaxHP = 30;
		iCurHP = 30;
		iShield = 0;
		iAttack = 1;
		iDefence = 1;
		fSpeed = 300.f;
		bAlive = true;
		fRecogDist = 300.f;
		fAttackDist = 100.f;
	}

	void ErodedHeavyInfantryMonsterDefaultSetting()
	{
		iMaxHP = 50;
		iCurHP = 50;
		iShield = 0;
		iAttack = 1;
		iDefence = 1;
		fSpeed = 300.f;
		bAlive = true;
		fRecogDist = 500.f;
		fAttackDist = 200.f;
	}

	void BossMonsterDefaultSetting()
	{
		iMaxHP = 100;
		iCurHP = 100;
		iShield = 0;
		iAttack = 1;
		iDefence = 1;
		fSpeed = 300.f;
		bAlive = true;
		fRecogDist = 500.f;
		fAttackDist = 200.f;
	}

	void TakeDamage(int32 iDamage)
	{
		assert(iDamage > 0);

		if (iCurHP <= iDamage)
		{
			iCurHP = 0;
			bAlive = false;
		}

		if (bAlive)
			iCurHP -= iDamage;
	}

	void IncreaseHP(int32 iHeal)
	{
		iCurHP += iHeal;
		if (iCurHP > iMaxHP)
			iCurHP = iMaxHP;
	}

	float GetHPRatio()
	{
		assert(iMaxHP > 0);
		return iCurHP / static_cast<float>(iMaxHP);
	}

	bool IsAlive() { return bAlive; }

public:
	int32 iMaxHP;
	int32 iCurHP;
	int32 iShield;
	int32 iAttack;
	int32 iDefence;
	float fSpeed;
	bool  bAlive;
	float fRecogDist;
	float fAttackDist;
	float fCriticalPercent;
};

enum class ATTACK_TYPE
{
	MELEE,
	MISSILE,
};

struct AttackInfo
{
	AttackInfo()
	{
		memset(this, 0, sizeof(AttackInfo));
	}

	explicit AttackInfo(shared_ptr<class Animation> pAnimation, float fStartAngle, float fEndAngle, float fRadius, uint8 iEnum = 0)
		: pAnimation(pAnimation)
		, fStartAngle(fStartAngle)
		, fEndAngle(fEndAngle)
		, fRadius(fRadius)
		, iEnum(iEnum)
		, bUse(true)
	{}

	shared_ptr<Animation> pAnimation;
	float fStartAngle;
	float fEndAngle;
	float fRadius;
	uint8 iEnum;
	bool bUse;
};



enum class ATTACK_ORDER
{
	ATTACK_A,
	ATTACK_B,
	ATTACK_C,
	ATTACK_D,
	ATTACK_E,
	END,
};

enum
{
	ATTACK_ORDER_COUNT = ATTACK_ORDER::END,
	TILE_SIZE = 64,
	TILE_HALF_SIZE = TILE_SIZE / 2,
};

namespace Conv
{
	using namespace DirectX::SimpleMath;
	static Quaternion PxQuatToQuat(const PxQuat& pxQuat)
	{
		return Quaternion(pxQuat.x, pxQuat.y, pxQuat.z, pxQuat.w);
	}

	static wstring AddressToWstring(void* pAddress)
	{
		assert(pAddress);
		uint64 iAddress = reinterpret_cast<uint64>(pAddress);
		return std::to_wstring(iAddress);
	}

	template<typename T, typename U>
	static shared_ptr<T> BaseToDeclare(shared_ptr<U> pBase)
	{
		if constexpr (!std::is_base_of_v<U, T>)
			assert(nullptr);
		return dynamic_pointer_cast<T>(pBase);
	}

	static Vec2 Vec3ToTileAlignVec2(Vec3 vVec3)
	{
		Vec2 vTileAlignVec = { vVec3.x, vVec3.y };
		vTileAlignVec.x = static_cast<float>(static_cast<int32>((vTileAlignVec.x / TILE_SIZE)) * TILE_SIZE);
		vTileAlignVec.y = static_cast<float>(static_cast<int32>((vTileAlignVec.y / TILE_SIZE)) * TILE_SIZE);
		return vTileAlignVec;
	}

	static ImVec3 Vec3ToImVec3(Vec3 vVec3)
	{
		return ImVec3{ vVec3.x, vVec3.y, vVec3.z };
	}

	static Vec3 ImVec3ToVec3(ImVec3 vVec3)
	{
		return Vec3(vVec3.x, vVec3.y, vVec3.z);
	}

	static Vec2 ImVec2ToVec2(ImVec2 vVec2)
	{
		return Vec2(vVec2.x, vVec2.y);
	}

	static PxVec3 Vec3ToPxVec3(Vec3 vVec3)
	{
		return PxVec3(vVec3.x, vVec3.y, vVec3.z);
	}

	static PxExtendedVec3 Vec3ToPxExtendedVec3(Vec3 vVec3)
	{
		return PxExtendedVec3(vVec3.x, vVec3.y, vVec3.z);
	}

	static PxVec4 Vec4ToPxVec4(Vec4 vVec3)
	{
		return PxVec4(vVec3.x, vVec3.y, vVec3.z, vVec3.w);
	}

	static PxMat44 Mat44ToPxMat44(Matrix matMatrix)
	{
		PxMat44 pxMat44 = {};
		pxMat44.column0 = PxVec4(matMatrix._11, matMatrix._12, matMatrix._13, matMatrix._14);
		pxMat44.column1 = PxVec4(matMatrix._21, matMatrix._22, matMatrix._23, matMatrix._24);
		pxMat44.column2 = PxVec4(matMatrix._31, matMatrix._32, matMatrix._33, matMatrix._34);
		pxMat44.column3 = PxVec4(matMatrix._41, matMatrix._42, matMatrix._43, matMatrix._44);

		return pxMat44;
	}

	static Vec3 PxVec3ToVec3(PxVec3 pxVec3)
	{
		return Vec3(pxVec3.x, pxVec3.y, pxVec3.z);
	}

	static Vec3 PxExtendedVec3ToVec3(PxExtendedVec3 pxExVec3)
	{
		return Vec3(
			static_cast<float>(pxExVec3.x), 
			static_cast<float>(pxExVec3.y), 
			static_cast<float>(pxExVec3.z));
	}

	static Vec4 PxVec4ToVec4(PxVec4 pxVec3)
	{
		return Vec4(pxVec3.x, pxVec3.y, pxVec3.z, pxVec3.w);
	}

	static Matrix PxMat44ToMat44(PxMat44 pxMatrix)
	{
		Matrix mat = {};
		mat._11 = pxMatrix.column0.x;
		mat._12 = pxMatrix.column0.y;
		mat._13 = pxMatrix.column0.z;
		mat._14 = pxMatrix.column0.w;

		mat._21 = pxMatrix.column1.x;
		mat._22 = pxMatrix.column1.y;
		mat._23 = pxMatrix.column1.z;
		mat._24 = pxMatrix.column1.w;

		mat._31 = pxMatrix.column2.x;
		mat._32 = pxMatrix.column2.y;
		mat._33 = pxMatrix.column2.z;
		mat._34 = pxMatrix.column2.w;

		mat._41 = pxMatrix.column3.x;
		mat._42 = pxMatrix.column3.y;
		mat._43 = pxMatrix.column3.z;
		mat._44 = pxMatrix.column3.w;

		return mat;
	}

	static PxMat44 PxMat33ToPxMat44(PxMat33 pxMatrix)
	{
		PxMat44 mat = {};

		mat.column0.x = pxMatrix.column0.x;
		mat.column0.y = pxMatrix.column0.y;
		mat.column0.z = pxMatrix.column0.z;
		mat.column0.w = 0.f;

		mat.column1.x = pxMatrix.column1.x;
		mat.column1.y = pxMatrix.column1.y;
		mat.column1.z = pxMatrix.column1.z;
		mat.column1.w = 0.f;

		mat.column2.x = pxMatrix.column2.x;
		mat.column2.y = pxMatrix.column2.y;
		mat.column2.z = pxMatrix.column2.z;
		mat.column2.w = 0.f;

		mat.column3.x = 0.f;
		mat.column3.y = 0.f;
		mat.column3.z = 0.f;
		mat.column3.w = 1.f;

		return mat;
	}
}

struct Timer
{
public:
	Timer(float fEndTime)
		:m_fCurTime(0.f)
		,m_fEndTime(fEndTime)
		,m_bIsRunning(false)
		,m_bIsFinished(true)
	{}

	void Reset()
	{
		m_fCurTime = 0.f;
		m_bIsRunning = false;
		m_bIsFinished = false;
	}

	void Start()
	{
		m_fCurTime = 0.f;
		m_bIsRunning = true;
		m_bIsFinished = false;
	}

	void Stop()
	{
		m_fCurTime = 0.f;
		m_bIsRunning = false;
		m_bIsFinished = false;
	}

	void Update(float fDeltaTime)
	{
		if (m_bIsFinished)
			return;

		if (m_bIsRunning)
		{
			m_fCurTime += fDeltaTime;
			if (m_fCurTime > m_fEndTime)
			{
				m_fCurTime = m_fEndTime;
				m_bIsFinished = true;
			}
		}
	}

	void SetEndTime(float fEndTime)
	{
		m_fEndTime = fEndTime;
	}

	bool IsRunning()
	{
		return m_bIsRunning;
	}

	bool IsFinished()
	{
		return m_bIsFinished;
	}

	float GetProgress() const
	{
		if (m_fEndTime == 0.f)
			return 1.f;

		return std::clamp(m_fCurTime / m_fEndTime, 0.f, 1.f);
	}
	
	void SetProgress(float fProgress)
	{
		m_fCurTime = m_fEndTime * fProgress;
	}

private:
	float m_fCurTime;
	float m_fEndTime;
	bool  m_bIsRunning;
	bool  m_bIsFinished;
};


#define DECLARE_SINGLE(type)  \
private:					  \
	type() {}				  \
	~type() {}				  \
							  \
public:						  \
	static type* GetInstance()\
	{						  \
		static type instance; \
		return &instance;	  \
	}						  \


#pragma region POOL_INTERFACE
#define DECLARE_POOL(name)\
public:\
friend class name##Pool;\
	static shared_ptr<name> Get()\
	{\
		if (!m_pPool)\
			m_pPool = make_unique<name##Pool>();\
		return m_pPool->Get();\
	}\
	static void Release(shared_ptr<name> p##name)\
	{\
		m_pPool->Release(p##name);\
	}\
	virtual void ReturnToPool() override\
	{\
		name::Release(static_pointer_cast<name>(shared_from_this()));\
	}\
private:\
class name##Pool											\
{															\
public:\
	name##Pool()\
		: m_vUse(INITIAL_POOL_COUNT, false)\
	{ \
		m_vPool.reserve(INITIAL_POOL_COUNT);\
		for (int i = 0; i < INITIAL_POOL_COUNT; ++i)\
		{\
			m_vPool.emplace_back(make_shared<name>());\
		}\
	}\
	~name##Pool() = default;\
public:\
	shared_ptr<name> Get()\
	{\
		for (uint32 i = 0; i < m_vUse.size(); ++i)\
		{\
			if (!m_vUse[i])\
			{\
				m_vUse[i] = true;\
				return m_vPool[i];\
			}\
		}\
		m_vPool.emplace_back(make_shared<name>());\
		m_vUse.push_back(true);\
		return m_vPool.back();\
	}\
	void Release(shared_ptr<name> p##name)\
	{\
		for (uint32 i = 0; i < m_vUse.size(); ++i)\
		{\
			if (p##name == m_vPool[i])\
			{\
				m_vUse[i] = false;\
				break;\
			}\
		}\
	}\
private:\
	std::vector<shared_ptr<name>> m_vPool;\
	std::vector<bool> m_vUse;\
};\
\
static unique_ptr<name##Pool> m_pPool;\
private:\
bool m_bUse = false;\

#define POOL_INIT(name) unique_ptr<name::name##Pool> name::m_pPool = nullptr

#pragma endregion

#define DEVICE g_pEngine->GetDevice()->GetDevice()
#define CONTEXT g_pEngine->GetContext()->GetContext()
#define PHYSICS g_pEngine->GetPhysics()->GetEnvironment()->GetPhysics()
#define PX_SCENE g_pEngine->GetPhysics()->GetEnvironment()->GetPhysScene()
#define UTILITY g_pEngine->GetUtility()
#define MAP_TOOL g_pEngine->GetUtility()->GetTool()->GetMapEditor()
#define ANIMATION_TOOL g_pEngine->GetUtility()->GetTool()->GetAnimEditor()
#define FONT g_pEngine->GetFont()
#define GET_SINGLE(type) type::GetInstance()
#define CONST_BUFFER(type) g_pEngine->GetCB(type)
#define WORLD_DELTA_TIME GET_SINGLE(Clock)->GetWorldDeltaTime()
#define OBJECT_DELTA_TIME GET_SINGLE(Clock)->GetObjectDeltaTime()
#define IS_PRESS(key) GET_SINGLE(Input)->GetButtonPress(key)
#define IS_DOWN(key) GET_SINGLE(Input)->GetButtonDown(key)
#define IS_UP(key) GET_SINGLE(Input)->GetButtonUp(key)
#define IS_NONE(key) GET_SINGLE(Input)->GetButtonNone(key)
#define VEC3_RIGHT_NORMAL Vec3(1.f, 0.f, 0.f)
#define VEC3_UP_NORMAL Vec3(0.f, 1.f, 0.f)
#define RANDOM(minNumber, maxNumber) rand() % (maxNumber - (minNumber - 1)) + minNumber

// Color
#define GRADE_COLOR Color::FromRGB(136, 96, 90)
#define NAME_COLOR Color::FromRGB(75, 53, 50)
#define COMMENT_COLOR Color::FromRGB(117, 86, 85)

extern unique_ptr<class Engine> g_pEngine;