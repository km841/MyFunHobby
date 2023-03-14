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

// ���� lib
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

// ���� typedef

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
	Vertex(Vec3 vPos, Vec2 vUV)
		: vPos(vPos), vUV(vUV)
	{}

	Vec3 vPos;
	Vec2 vUV;

public:
	static std::vector<Vertex> CreateHemisphereVertices(float fRadius, float fSlices)
	{
		std::vector<Vertex> vVertices;

		for (int i = 0; i < fSlices; ++i)
		{
			float theta = i / fSlices * 2.0f * XM_PI;
			Vec3 vVertex(fRadius * cosf(theta), fRadius * sinf(theta), 0.0f);
			Vec2 vUV = Vec2(cosf(theta), sinf(theta)) * 0.5f + Vec2{ 0.5f, 0.5f };
			vVertices.push_back({ vVertex, vUV });
		}

		return vVertices;
	}

	static std::vector<Vertex> CreateBoxVertices(Vec3 vBoxHalfSize)
	{
		std::vector<Vertex> vVertices;

		vVertices.push_back({ Vec3(-vBoxHalfSize.x, vBoxHalfSize.y, 0.f), Vec2(0.f, 0.f) });
		vVertices.push_back({ Vec3(vBoxHalfSize.x, vBoxHalfSize.y, 0.f), Vec2(1.f, 0.f) });
		vVertices.push_back({ Vec3(vBoxHalfSize.x, -vBoxHalfSize.y, 0.f), Vec2(1.f, 1.f) });
		vVertices.push_back({ Vec3(-vBoxHalfSize.x, -vBoxHalfSize.y, 0.f), Vec2(0.f, 1.f) });

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

	// �̱���
	static std::pair<std::vector<Vertex>, std::vector<uint32>> CreateCapsuleVerticesAndIndices(float fRadius, float fHeight, float fSlices)
	{
		std::vector<Vertex> vVertices;
		std::vector<uint32> vIndices;

		return make_pair(vVertices, vIndices);
	}
};

struct TransformParams
{
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

namespace Conv
{
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
}


enum class CBV_REGISTER : uint8
{
	b0,
	b1,
	b2,
	b3,
	b4,


	END,
};

enum class SRV_REGISTER : uint8
{
	t0,
	t1,
	t2,
	t3,
	t4,


	END,
};

enum class CONSTANT_BUFFER_TYPE
{
	TRANSFORM,
	MATERIAL,
	END,
};

enum
{
	CONSTANT_BUFFER_TYPE_COUNT = CONSTANT_BUFFER_TYPE::END,
	INITIAL_POOL_COUNT = 1000,
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
		m_vPool.emplace_back();\
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
#define UTILITY g_pEngine->GetUtility()
#define POOL g_pEngine->GetObjectPool()
#define GET_SINGLE(type) type::GetInstance()
#define CONST_BUFFER(type) g_pEngine->GetCB(type)
#define DELTA_TIME GET_SINGLE(Timer)->GetDeltaTime()
#define IS_PRESS(key) GET_SINGLE(Input)->GetButtonPress(key)
#define IS_DOWN(key) GET_SINGLE(Input)->GetButtonDown(key)
#define IS_UP(key) GET_SINGLE(Input)->GetButtonUp(key)

enum
{
	SWAP_CHAIN_BUFFER_COUNT = 1,
	CBV_REGISTER_COUNT = CBV_REGISTER::END,
	SRV_REGISTER_COUNT = SRV_REGISTER::END,
};

extern unique_ptr<class Engine> g_pEngine;