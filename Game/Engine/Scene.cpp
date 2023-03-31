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
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->ClearRenderTargetView();
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTarget();

	for (const shared_ptr<Camera>& pCamera : m_vCameras)
	{
		pCamera->Render();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> pGameObject)
{
	if (pGameObject->GetCamera())
		m_vCameras.push_back(pGameObject->GetCamera());

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

		shared_ptr<Tile> pTile = Tile::Get();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Forward");
		pMaterial->SetShader(pShader);

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szTexPath, szTexPath);
		assert(pTexture);
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pTile->AddComponent(pMeshRenderer);
		pTile->AddComponent(make_shared<Transform>());
		pTile->AddComponent(make_shared<Physical>(ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f)));
		pTile->AddComponent(make_shared<Collider>());
		pTile->AddComponent(make_shared<DebugRenderer>());

		pTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));
		pTile->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 100.f));

		// 잠들어 있는 Component 깨우기
		pTile->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));
	}

	ifs.close();
}
