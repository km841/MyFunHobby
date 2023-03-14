#include "pch.h"
#include "TownScene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraMoveScript.h"
#include "Engine.h"
#include "Resources.h"
#include "Controller.h"
#include "PlayerMoveScript.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Physical.h"
#include "Player.h"
#include "SceneChangeEvent.h"
#include "DebugRenderer.h"

TownScene::TownScene()
{
}

TownScene::~TownScene()
{
}

void TownScene::Awake()
{
	Scene::Awake();
}

void TownScene::Start()
{
	Scene::Start();
}

void TownScene::Update()
{
	Scene::Update();
}

void TownScene::LateUpdate()
{
	Scene::LateUpdate();
}

void TownScene::FinalUpdate()
{
	Scene::FinalUpdate();
}

void TownScene::Render()
{
	Scene::Render();
}

void TownScene::Enter()
{
	// Background
	{
		shared_ptr<GameObject> pGameObject = GameObject::Get();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Image_Town.png");

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward");
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 25.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(19.f, 12.f, 1.f));

		AddGameObject(pGameObject);
	}

	// Player
	{
		shared_ptr<Player> pGameObject = make_shared<Player>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Image_LittleBone.tga");

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Alpha");
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Physical>(ACTOR_TYPE::CHARACTER, GEOMETRY_TYPE::BOX, Vec3(1.f, 1.f, 1.f)));
		pGameObject->AddComponent(make_shared<Controller>());
		pGameObject->AddComponent(make_shared<PlayerMoveScript>());
		pGameObject->AddComponent(make_shared<RigidBody>(ACTOR_TYPE::CHARACTER));
		pGameObject->AddComponent(make_shared<Collider>());
		pGameObject->AddComponent(make_shared<DebugRenderer>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 5.f, 24.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(0.7f, 1.f, 1.f));

		AddGameObject(pGameObject);
	}

	// NPC
	{
		shared_ptr<GameObject> pGameObject = GameObject::Get();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Image_NPC.tga");

		shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Alpha");

		shared_ptr<Material> pMaterial = make_shared<Material>();
		pMaterial->SetShader(pShader);
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		//pGameObject->AddComponent(make_shared<Physical>(ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::BOX, Vec3(1.f, 1.f, 1.f)));
		//pGameObject->AddComponent(make_shared<RigidBody>(ACTOR_TYPE::DYNAMIC));
		//pGameObject->AddComponent(make_shared<Collider>());
		//pGameObject->AddComponent(make_shared<DebugRenderer>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 3.f, fHeight / 2.f - 5.f, 24.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.5f, 1.5f, 1.f));

		AddGameObject(pGameObject);
	}

	// Camera
	{
		shared_ptr<GameObject> pGameObject = GameObject::Get();

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		pGameObject->AddComponent(make_shared<CameraMoveScript>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 0.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);
	}


	// GameObject를 깨우는 작업
	Awake();
}

void TownScene::Exit()
{
}
