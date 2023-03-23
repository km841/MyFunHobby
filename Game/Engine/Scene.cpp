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

Scene::Scene(SCENE_TYPE eSceneType)
	: m_eSceneType(eSceneType)
{

}

Scene::~Scene()
{
}

void Scene::Awake()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->FinalUpdate();
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

	m_vGameObjects.push_back(pGameObject);
}

std::vector<shared_ptr<GameObject>> Scene::GetGameObjects(LAYER_TYPE eLayerType)
{
	std::vector<shared_ptr<GameObject>> vGameObjects;

	for (const auto& pGameObject : m_vGameObjects)
	{
		if (eLayerType == pGameObject->GetLayerType())
		{
			vGameObjects.push_back(pGameObject);
		}
	}

	return vGameObjects;
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
		shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Alpha");
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
		pTile->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 1.f));

		// 잠들어 있는 Component 깨우기
		pTile->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));
	}

	ifs.close();
}
