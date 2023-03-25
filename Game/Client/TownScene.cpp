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
#include "Animation.h"
#include "Animator.h"
#include "Input.h"
#include "Monster.h"
#include "CollisionManager.h"

TownScene::TownScene()
	: Scene(SCENE_TYPE::TOWN)
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
	Load(L"..\\Resources\\Map\\DefaultMap.map");
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::MONSTER, LAYER_TYPE::TILE);

	// Player
	{
		shared_ptr<Player> pGameObject = make_shared<Player>();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(50.f, 50.f, 1.f)));
		pGameObject->AddComponent(make_shared<Controller>());
		pGameObject->AddComponent(make_shared<PlayerMoveScript>());
		pGameObject->AddComponent(make_shared<RigidBody>(true));
		pGameObject->AddComponent(make_shared<Collider>());
		pGameObject->AddComponent(make_shared<DebugRenderer>());
		pGameObject->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Idle", L"..\\Resources\\Animation\\littlebone_idle.anim");
		shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Walk", L"..\\Resources\\Animation\\littlebone_walk.anim");
		shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpRise", L"..\\Resources\\Animation\\littlebone_jump_rise.anim");
		shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpFall", L"..\\Resources\\Animation\\littlebone_jump_fall.anim");

		pGameObject->GetAnimator()->AddAnimation(L"LittleBone_Idle", pIdleAnimation);
		pGameObject->GetAnimator()->AddAnimation(L"LittleBone_Walk", pWalkAnimation);
		pGameObject->GetAnimator()->AddAnimation(L"LittleBone_JumpRise", pJumpRiseAnimation);
		pGameObject->GetAnimator()->AddAnimation(L"LittleBone_JumpFall", pJumpFallAnimation);
		pGameObject->GetAnimator()->Play(L"LittleBone_Idle");

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 300.f, fHeight / 2.f - 5.f, 1.f));

		AddGameObject(pGameObject);
	}

	// Compute Shader
	{
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Compute");
		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Create(D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, 1024, 1024);

		shared_ptr<Texture> pNoiseTexture = GET_SINGLE(Resources)->Load<Texture>(L"NoiseTexture", L"..\\Resources\\Texture\\Image_NoiseTexture.tga");
		pMaterial->SetTexture(0, pTexture);
		pMaterial->SetTexture(1, pNoiseTexture);
		pMaterial->SetVec3(0, pNoiseTexture->GetTexSize());

		pMaterial->Dispatch(1, 1024, 1);
		GET_SINGLE(Resources)->Add<Texture>(L"ComputeTexture", pTexture);
	}

	// Monster
	{
		shared_ptr<Monster> pGameObject = make_shared<Monster>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		//shared_ptr<Texture> pTexture = make_shared<Texture>();
		//pTexture->Load(L"..\\Resources\\Texture\\Image_NPC.tga");

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(L"ComputeTexture");

		shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Alpha");

		shared_ptr<Material> pMaterial = make_shared<Material>();
		pMaterial->SetShader(pShader);
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(110.f, 110.f, 1.f), MassProperties(10.f, 10.f, 10.f)));
		pGameObject->AddComponent(make_shared<RigidBody>());
		pGameObject->AddComponent(make_shared<Collider>());
		pGameObject->AddComponent(make_shared<DebugRenderer>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 30.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(110.f, 110.f, 1.f));

		AddGameObject(pGameObject);
	}



	// Background
	//{
	//	shared_ptr<GameObject> pGameObject = GameObject::Get();
	//	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	//	shared_ptr<Texture> pTexture = make_shared<Texture>();
	//	pTexture->Load(L"..\\Resources\\Texture\\Image_Town.png");
	//	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward");
	//	pMaterial->SetTexture(0, pTexture);
	//	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	//	pMeshRenderer->SetMaterial(pMaterial);
	//	pMeshRenderer->SetMesh(pMesh);
	//	pGameObject->AddComponent(pMeshRenderer);
	//	pGameObject->AddComponent(make_shared<Transform>());
	//	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	//	float fHeight = static_cast<float>(g_pEngine->GetHeight());
	//	pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
	//	pGameObject->GetTransform()->SetLocalScale(Vec3(800.f, 450.f, 1.f));

	//	AddGameObject(pGameObject);
	//}

	// Camera
	{
		shared_ptr<GameObject> pGameObject = GameObject::Get();

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		pGameObject->AddComponent(make_shared<CameraMoveScript>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);
	}


	// GameObject를 깨우는 작업
	Awake();
}

void TownScene::Exit()
{
}
