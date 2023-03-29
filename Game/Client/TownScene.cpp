#include "pch.h"
#include "TownScene.h"
#include "Engine.h"
#include "GameObject.h"

/* Event */
#include "SceneChangeEvent.h"

/* Interface */
#include "PlayerInterfaceHUD.h"
#include "HealthBarHUD.h"
#include "SkulHeadHUD.h"
#include "DialogueUI.h"

/* Script */
#include "PlayerHealthBarShowScript.h"
#include "CameraFadeInOutScript.h"
#include "PlayerTrackingScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"

/* Manager */
#include "Resources.h"
#include "Input.h"
#include "CollisionManager.h"
#include "UIManager.h"

/* GameObject */
#include "Player.h"
#include "Monster.h"
#include "NPC_Witch.h"
#include "NPC_Wolf.h"
#include "NPC_Wizard.h"
#include "NPC_Ogre.h"

/* Resources */
#include "Animation.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

/* Component */
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Controller.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Physical.h"
#include "DebugRenderer.h"
#include "Animator.h"

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
	//Load(L"..\\Resources\\Map\\DefaultMap.map");
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::MONSTER, LAYER_TYPE::TILE);

	shared_ptr<Player> pPlayer = nullptr;
	// Player
	{
		pPlayer = make_shared<Player>();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pPlayer->AddComponent(pMeshRenderer);
		pPlayer->AddComponent(make_shared<Transform>());
		pPlayer->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(50.f, 50.f, 1.f)));
		pPlayer->AddComponent(make_shared<Controller>());
		pPlayer->AddComponent(make_shared<PlayerMoveScript>());
		pPlayer->AddComponent(make_shared<RigidBody>(true));
		pPlayer->AddComponent(make_shared<Collider>());
		pPlayer->AddComponent(make_shared<DebugRenderer>());
		pPlayer->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Idle", L"..\\Resources\\Animation\\LittleBone\\littlebone_idle.anim");
		shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Walk", L"..\\Resources\\Animation\\LittleBone\\littlebone_walk.anim");
		shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpRise", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_rise.anim");
		shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpFall", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_fall.anim");
		shared_ptr<Animation> pAttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackA", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_a.anim");
		shared_ptr<Animation> pAttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackB", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_b.anim");
		

		pPlayer->GetAnimator()->AddAnimation(L"LittleBone_Idle", pIdleAnimation);
		pPlayer->GetAnimator()->AddAnimation(L"LittleBone_Walk", pWalkAnimation);
		pPlayer->GetAnimator()->AddAnimation(L"LittleBone_JumpRise", pJumpRiseAnimation);
		pPlayer->GetAnimator()->AddAnimation(L"LittleBone_JumpFall", pJumpFallAnimation);
		pPlayer->GetAnimator()->AddAnimation(L"LittleBone_AttackA", pAttackA_Animation);
		pPlayer->GetAnimator()->AddAnimation(L"LittleBone_AttackB", pAttackB_Animation);
		pPlayer->GetAnimator()->Play(L"LittleBone_Idle");

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pPlayer->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 300.f, fHeight / 2.f - 5.f, 100.f));

		AddGameObject(pPlayer);
	}


	shared_ptr<PlayerInterfaceHUD> pInterfaceHUD = nullptr;
	// Player Interface HUD
	{
		pInterfaceHUD = make_shared<PlayerInterfaceHUD>();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"PlayerInterfaceHUD", L"..\\Resources\\Texture\\HUD\\HUD_Player_Normal_Frame.tga");
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pInterfaceHUD->AddComponent(pMeshRenderer);
		pInterfaceHUD->AddComponent(make_shared<Transform>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pInterfaceHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 420.f, fHeight / 2.f - 270.f, 80.f));
		pInterfaceHUD->GetTransform()->SetLocalScale(Vec3(203.f, 66.f, 1.f));

		AddGameObject(pInterfaceHUD);
	}

	// Skul Head HUD
	{
		shared_ptr<SkulHeadHUD> pSkulHeadHUD = make_shared<SkulHeadHUD>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"LittleBoneHeadHUD", L"..\\Resources\\Texture\\HUD\\HUD_Skul_Head.tga");
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pSkulHeadHUD->AddComponent(pMeshRenderer);
		pSkulHeadHUD->AddComponent(make_shared<Transform>());
		pSkulHeadHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pSkulHeadHUD->GetTransform()->SetLocalPosition(Vec3(-145.f, 18.f, -10.f));
		pSkulHeadHUD->GetTransform()->SetLocalScale(Vec3(45.f, 45.f, 0.f));

		AddGameObject(pSkulHeadHUD);
	}

	// Health Bar HUD
	{
		shared_ptr<HealthBarHUD> pHealthBarHUD = make_shared<HealthBarHUD>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"HP")->Clone();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"HealthBarHUD", L"..\\Resources\\Texture\\HUD\\HealthBar\\HUD_Player_HealthBar.tga");
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pHealthBarHUD->AddComponent(pMeshRenderer);
		pHealthBarHUD->AddComponent(make_shared<PlayerHealthBarShowScript>(pPlayer));
		pHealthBarHUD->AddComponent(make_shared<Transform>());
		pHealthBarHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pHealthBarHUD->GetTransform()->SetLocalPosition(Vec3(1.f, -32.5f, -10.f));
		pHealthBarHUD->GetTransform()->SetLocalScale(Vec3(115.f, 8.f, 1.f));

		AddGameObject(pHealthBarHUD);
	}

	// Ground
	{
		shared_ptr<GameObject> pGround = make_shared<GameObject>(LAYER_TYPE::TILE);
		pGround->AddComponent(make_shared<Transform>());
		pGround->AddComponent(make_shared<Physical>(ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(2400.f, 400.f, 1.f)));
		pGround->AddComponent(make_shared<Collider>());
		pGround->AddComponent(make_shared<DebugRenderer>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGround->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 800.f, fHeight / 2.f - 650.f, 100.f));
		pGround->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));

		AddGameObject(pGround);
	}

	// Compute Shader
	{
		//shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Compute");
		//shared_ptr<Texture> pTexture = make_shared<Texture>();
		//pTexture->Create(D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, 1024, 1024);

		//shared_ptr<Texture> pNoiseTexture = GET_SINGLE(Resources)->Load<Texture>(L"NoiseTexture", L"..\\Resources\\Texture\\Image_NoiseTexture.tga");
		//pMaterial->SetTexture(0, pTexture);
		//pMaterial->SetTexture(1, pNoiseTexture);
		//pMaterial->SetVec3(0, pNoiseTexture->GetTexSize());

		//pMaterial->Dispatch(1, 1024, 1);
		//GET_SINGLE(Resources)->Add<Texture>(L"ComputeTexture", pTexture);
	}

	// Monster
	//{
	//	shared_ptr<Monster> pGameObject = make_shared<Monster>();

	//	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	//	shared_ptr<Texture> pTexture = make_shared<Texture>();
	//	pTexture->Load(L"..\\Resources\\Texture\\Image_NPC.tga");

	//	//shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(L"ComputeTexture");
	//	shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Forward");

	//	shared_ptr<Material> pMaterial = make_shared<Material>();
	//	pMaterial->SetShader(pShader);
	//	pMaterial->SetTexture(0, pTexture);

	//	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	//	pMeshRenderer->SetMaterial(pMaterial);
	//	pMeshRenderer->SetMesh(pMesh);

	//	pGameObject->AddComponent(pMeshRenderer);
	//	pGameObject->AddComponent(make_shared<Transform>());
	//	pGameObject->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(110.f, 110.f, 1.f)));
	//	pGameObject->AddComponent(make_shared<RigidBody>());
	//	pGameObject->AddComponent(make_shared<Collider>());
	//	pGameObject->AddComponent(make_shared<DebugRenderer>());

	//	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	//	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	//	pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 250.f, fHeight / 2.f, 100.f));
	//	pGameObject->GetTransform()->SetLocalScale(pTexture->GetTexSize());

	//	AddGameObject(pGameObject);
	//}

	//Background
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Map\\Image_Town.tga");
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		pMaterial->SetTexture(0, pTexture);
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 800.f, fHeight / 2.f, 140.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(2400.f, 450.f, 1.f));

		AddGameObject(pGameObject);
	}


	// Camera
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		pGameObject->AddComponent(make_shared<CameraMoveScript>());
		pGameObject->AddComponent(make_shared<PlayerTrackingScript>(static_pointer_cast<Player>(m_vGameObjects[static_cast<uint8>(LAYER_TYPE::PLAYER)][0])));

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);

		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::HUD, true);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::UI, true);
	}


	// UI Camera
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);

		pGameObject->GetCamera()->EnableAllCullingMask();
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::HUD, false);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::UI, false);
	}



	// NPC_Witch
	{
		shared_ptr<NPC_Witch> pWitch = make_shared<NPC_Witch>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pWitch->AddComponent(pMeshRenderer);
		pWitch->AddComponent(make_shared<Transform>());
		pWitch->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(400.f, 120.f, 1.f)));
		pWitch->AddComponent(make_shared<RigidBody>());
		pWitch->AddComponent(make_shared<Collider>());
		pWitch->AddComponent(make_shared<DebugRenderer>());
		pWitch->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Witch_Idle", L"..\\Resources\\Animation\\Witch\\witch_idle.anim");
		pWitch->GetAnimator()->AddAnimation(L"Witch_Idle", pAnimation);
		pWitch->GetAnimator()->Play(L"Witch_Idle");

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pWitch->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 300.f, fHeight / 2.f - 115.f, 110.f));

		AddGameObject(pWitch);
	}

	// NPC_Wolf
	{
		shared_ptr<NPC_Witch> pWolf = make_shared<NPC_Witch>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pWolf->AddComponent(pMeshRenderer);
		pWolf->AddComponent(make_shared<Transform>());
		pWolf->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(217.f, 144.f, 1.f)));
		pWolf->AddComponent(make_shared<RigidBody>());
		pWolf->AddComponent(make_shared<Collider>());
		pWolf->AddComponent(make_shared<DebugRenderer>());
		pWolf->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Wolf_Idle", L"..\\Resources\\Animation\\Wolf\\wolf_idle.anim");
		pWolf->GetAnimator()->AddAnimation(L"Wolf_Idle", pAnimation);
		pWolf->GetAnimator()->Play(L"Wolf_Idle");

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pWolf->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 600.f, fHeight / 2.f - 80.f, 110.f));

		AddGameObject(pWolf);
	}

	// NPC_Ogre
	{
		shared_ptr<NPC_Ogre> pOgre = make_shared<NPC_Ogre>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pOgre->AddComponent(pMeshRenderer);
		pOgre->AddComponent(make_shared<Transform>());
		pOgre->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(227.f, 151.f, 1.f)));
		pOgre->AddComponent(make_shared<RigidBody>());
		pOgre->AddComponent(make_shared<Collider>());
		pOgre->AddComponent(make_shared<DebugRenderer>());
		pOgre->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Ogre_Idle", L"..\\Resources\\Animation\\Ogre\\ogre_idle.anim");
		pOgre->GetAnimator()->AddAnimation(L"Ogre_Idle", pAnimation);
		pOgre->GetAnimator()->Play(L"Ogre_Idle");

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pOgre->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 1200.f, fHeight / 2.f - 70.f, 110.f));

		AddGameObject(pOgre);
	}

	// NPC_Wizard
	{
		shared_ptr<NPC_Wizard> pWizard = make_shared<NPC_Wizard>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pWizard->AddComponent(pMeshRenderer);
		pWizard->AddComponent(make_shared<Transform>());
		pWizard->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(221.f, 151.f, 1.f)));
		pWizard->AddComponent(make_shared<RigidBody>());
		pWizard->AddComponent(make_shared<Collider>());
		pWizard->AddComponent(make_shared<DebugRenderer>());
		pWizard->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Wizard_Idle", L"..\\Resources\\Animation\\Wizard\\wizard_idle.anim");
		pWizard->GetAnimator()->AddAnimation(L"Wizard_Idle", pAnimation);
		pWizard->GetAnimator()->Play(L"Wizard_Idle");

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pWizard->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 2000.f, fHeight / 2.f - 70.f, 110.f));

		AddGameObject(pWizard);
	}


	
	AddGameObject(GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE));
	GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->Disable();
	


	// Fade In/Out Object
	{
		shared_ptr<UI> pUI = make_shared<UI>();

		pUI->AddComponent(make_shared<Transform>());

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"FadeInOut");

		auto [vVertices, vIndices] = Vertex::CreateBoxVerticesAndIndicesTri(Vec3(1.f, 1.f, 1.f));
		shared_ptr<Mesh> pMesh = make_shared<Mesh>();

		pMesh->Init(vVertices, vIndices);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pUI->AddComponent(pMeshRenderer);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pUI->AddComponent(make_shared<CameraFadeInOutScript>(m_vCameras[1]));

		pUI->GetTransform()->SetLocalScale(Vec3(1600.f, 900.f, 10.f));
		pUI->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));

		AddGameObject(pUI);
	}

	m_vCameras[1]->SetCameraEffect(CAMERA_EFFECT::FADE_IN);

	// GameObject를 깨우는 작업
	Awake();
}

void TownScene::Exit()
{
}
