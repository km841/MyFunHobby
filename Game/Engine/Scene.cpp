#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"
#include "Camera.h"
#include "Physics.h"
#include "Tile.h"
#include "Resources.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "DebugRenderer.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "HUD.h"
#include "UI.h"
#include "AfterImage.h"
#include "Light.h"
#include "ObjectFactory.h"

std::array<std::vector<shared_ptr<GameObject>>, GLOBAL_OBJECT_TYPE_COUNT> Scene::s_vGlobalObjects;

Scene::Scene(SCENE_TYPE eSceneType)
	: m_eSceneType(eSceneType)
{

}

Scene::~Scene()
{
}

void Scene::Awake()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->Awake();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->Awake();
		}
	}
}

void Scene::Start()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->Start();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->Start();
		}
	}
}

void Scene::Update()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->Update();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->Update();
		}
	}
}

void Scene::LateUpdate()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->LateUpdate();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->LateUpdate();
		}
	}
}

void Scene::FinalUpdate()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->FinalUpdate();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->FinalUpdate();
		}
	}
}

void Scene::Render()
{
	// RenderTarget Clear
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->ClearRenderTargetView();
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->ClearRenderTargetView();
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->ClearRenderTargetView();

	// Deferred Rendering
	Render_Deferred();

	// Light Rendering
	PushLightData();
	Render_Lights();

	// G-Buffer Merge & Rendering
	Render_Final();

	// Forward Rendering
	Render_Forward();
}

void Scene::Render_Lights()
{
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->OMSetRenderTarget();
	shared_ptr<Camera> pMainCamera = m_vCameras[0];
	for (auto& pLight : m_vLights)
	{
		pLight->Render(pMainCamera);
	}
}

void Scene::Render_Final()
{
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTarget(1);

	GET_SINGLE(Resources)->Get<Material>(L"Final")->PushGraphicData();
	GET_SINGLE(Resources)->LoadRectMesh()->Render();
}

void Scene::Render_Forward()
{
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTarget(1);
	shared_ptr<Camera> pCamera = m_vCameras[0];
	pCamera->Render_Forward();

	for (const shared_ptr<Camera>& pSubCamera : m_vCameras)
	{
		if (pCamera == pSubCamera)
			continue;

		pSubCamera->SortGameObject();
		pSubCamera->Render_Forward();
	}
}

void Scene::Render_Deferred()
{
	shared_ptr<Camera> pCamera = m_vCameras[0];
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->OMSetRenderTarget();
	pCamera->SortGameObject();
	pCamera->Render_Deferred();
}

void Scene::PushLightData()
{
	LightParams lightParams = {};

	for (auto& pLight : m_vLights)
	{
		const LightInfo& lightInfo = pLight->GetLightInfo();

		pLight->SetLightIndex(lightParams.iLightCount);

		lightParams.Lights[lightParams.iLightCount] = lightInfo;
		lightParams.iLightCount++;
	}

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::LIGHT)->PushData(&lightParams, sizeof(lightParams));
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::LIGHT)->Mapping();
}

void Scene::AddGameObject(shared_ptr<GameObject> pGameObject)
{
	if (pGameObject->GetCamera())
		m_vCameras.push_back(pGameObject->GetCamera());

	if (pGameObject->GetLight())
		m_vLights.push_back(pGameObject->GetLight());

	if (pGameObject->GetPhysical())
		pGameObject->GetPhysical()->AddActorToPxScene();
	

	uint8 iLayerType = static_cast<uint8>(pGameObject->GetLayerType());

	if (iLayerType < SCENE_OBJECT_TYPE_COUNT)
		m_vSceneObjects[iLayerType].push_back(pGameObject);

	else
		s_vGlobalObjects[iLayerType - SCENE_OBJECT_TYPE_COUNT].push_back(pGameObject);
}

std::vector<shared_ptr<GameObject>>& Scene::GetGameObjects(LAYER_TYPE eLayerType)
{
	uint8 iLayerType = static_cast<uint8>(eLayerType);
	assert(iLayerType < LAYER_TYPE_COUNT);


	if (iLayerType < SCENE_OBJECT_TYPE_COUNT)
		return m_vSceneObjects[iLayerType];
	else
		return s_vGlobalObjects[iLayerType - SCENE_OBJECT_TYPE_COUNT];
}

void Scene::RemoveGameObject(shared_ptr<GameObject> pGameObject)
{
	if (pGameObject->GetCamera())
	{
		auto pFindIt = std::find(m_vCameras.begin(), m_vCameras.end(), pGameObject->GetCamera());
		if (pFindIt != m_vCameras.end())
			m_vCameras.erase(pFindIt);
	}

	if (pGameObject->GetLight())
	{
		auto pFindIt = std::find(m_vLights.begin(), m_vLights.end(), pGameObject->GetLight());
		if (pFindIt != m_vLights.end())
			m_vLights.erase(pFindIt);
	}

	auto& vGameObjects = GetGameObjects(pGameObject->GetLayerType());
	
	auto pFindIt = std::find(vGameObjects.begin(), vGameObjects.end(), pGameObject);
	if (pFindIt != vGameObjects.end())
		vGameObjects.erase(pFindIt);

}

void Scene::Load(const wstring& szPath)
{
	std::wifstream ifs(szPath, std::ios::in);

	uint32 iCount = 0;
	wstring szTexPath = {};
	Vec2 vTileAlignVec = {};

	ifs >> iCount;
	ifs.ignore(1);

	assert(iCount != 0);
	for (uint32 i = 0; i < iCount; ++i)
	{
		wstring szTexPath;
		Vec2 vTileAlignVec;

		ifs >> szTexPath;
		ifs.ignore(1);
		ifs >> vTileAlignVec.x >> vTileAlignVec.y;
		ifs.ignore(1);

		shared_ptr<Tile> pTile= GET_SINGLE(ObjectFactory)->CreateObjectFromPool<Tile>(
			L"Deferred",
			false,
			ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 50.f), MassProperties(100.f, 100.f, 0.01f),
			szTexPath);

		pTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));
		pTile->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 100.f));

		// 잠들어 있는 Component 깨우기
		pTile->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));
	}

	ifs.close();
}
