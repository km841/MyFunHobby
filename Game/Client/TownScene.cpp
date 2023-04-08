#include "pch.h"
#include "TownScene.h"
#include "Engine.h"


/* Event */
#include "SceneChangeEvent.h"

/* Interface */
#include "PlayerInterfaceHUD.h"
#include "HealthBarHUD.h"
#include "SkulThumnailHUD.h"
#include "DialogueUI.h"
#include "SkillBoxHUD.h"

/* Script */
#include "PlayerHealthBarShowScript.h"
#include "CameraFadeInOutScript.h"
#include "PlayerTrackingScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "PlayerFirstSkillShowScript.h"
#include "BackgroundMoveScript.h"
#include "GlobalEffectSettingScript.h"
#include "PlayerSkulThumnailScript.h"

/* Manager */
#include "Resources.h"
#include "Input.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "Cemetery.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "NPC_Witch.h"
#include "NPC_Wolf.h"
#include "NPC_Wizard.h"
#include "NPC_Ogre.h"
#include "GlobalEffect.h"

/* Resources */
#include "Animation.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

/* Components */
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Controller.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Physical.h"
#include "DebugRenderer.h"
#include "Animator.h"
#include "Movement.h"

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
	//GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);
	//GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER_PROJECTILE, LAYER_TYPE::TILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::NPC);
	//GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::NPC, LAYER_TYPE::PLAYER);
	//GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER_PROJECTILE, LAYER_TYPE::PLAYER);
	//GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::MONSTER, LAYER_TYPE::TILE);

	shared_ptr<Player> pPlayer = nullptr;
	// Player
	{
		pPlayer = make_shared<Player>();
		pPlayer->AddComponent(make_shared<Transform>());
		pPlayer->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(50.f, 50.f, 1.f)));
		pPlayer->AddComponent(make_shared<PlayerMoveScript>());
		pPlayer->AddComponent(make_shared<RigidBody>(true));
		pPlayer->AddComponent(make_shared<Collider>());
		pPlayer->AddComponent(make_shared<DebugRenderer>());
		pPlayer->AddComponent(make_shared<Movement>());
		pPlayer->ObtainSkul(GET_SINGLE(Cemetery)->Get(SKUL_TYPE::LITTLE_BONE));
		pPlayer->ObtainSkul(GET_SINGLE(Cemetery)->Get(SKUL_TYPE::HIGH_WARLOCK));

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pPlayer->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 300.f, fHeight / 2.f - 100.f, 100.f));

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

	// Skul Thumnail HUD
	{
		shared_ptr<SkulThumnailHUD> pSkulThumnailHUD = make_shared<SkulThumnailHUD>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pSkulThumnailHUD->AddComponent(pMeshRenderer);
		pSkulThumnailHUD->AddComponent(make_shared<Transform>());
		pSkulThumnailHUD->AddComponent(make_shared<PlayerSkulThumnailScript>(pPlayer, pSkulThumnailHUD));
		pSkulThumnailHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		
		pSkulThumnailHUD->GetTransform()->SetLocalPosition(Vec3(-145.f, 18.f, -10.f));
		pSkulThumnailHUD->GetTransform()->SetLocalScale(Vec3(45.f, 45.f, 0.f));

		AddGameObject(pSkulThumnailHUD);
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

	// Skill Box HUD
	{
		shared_ptr<SkillBoxHUD> pSkillBoxHUD = make_shared<SkillBoxHUD>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"SkillBox")->Clone();

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pSkillBoxHUD->AddComponent(pMeshRenderer);
		pSkillBoxHUD->AddComponent(make_shared<PlayerFirstSkillShowScript>(pPlayer, pSkillBoxHUD));
		pSkillBoxHUD->AddComponent(make_shared<Transform>());
		pSkillBoxHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pSkillBoxHUD->GetTransform()->SetLocalPosition(Vec3(-63.f, 11.5f, -10.f));
		pSkillBoxHUD->GetTransform()->SetLocalScale(Vec3(24.f, 24.f, 1.f));

		AddGameObject(pSkillBoxHUD);
	}

	// EffectTest
	//{
	//	shared_ptr<GlobalEffect> pGlobalEffect = make_shared<GlobalEffect>();

	//	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	//	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	//	//shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"SkillBoxLight", L"..\\Resources\\Texture\\HUD\\Image_SkillBox_Light1.tga");
	//	//pMaterial->SetTexture(1, pTexture);

	//	//pMaterial->SetTexture(1, GET_SINGLE(Resources)->Get<Texture>(L"DiffuseTarget"));

	//	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	//	pMeshRenderer->SetMaterial(pMaterial);
	//	pMeshRenderer->SetMesh(pMesh);

	//	pGlobalEffect->AddComponent(pMeshRenderer);
	//	pGlobalEffect->AddComponent(make_shared<Transform>());
	//	pGlobalEffect->AddComponent(make_shared<Animator>());
	//	pGlobalEffect->AddComponent(make_shared<GlobalEffectSettingScript>());

	//	pGlobalEffect->GetTransform()->SetParent(pInterfaceHUD->GetTransform());


	//	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Cooldown_Completion", L"..\\Resources\\Animation\\SkillBox\\cooldown_completion.anim");
	//	pGlobalEffect->GetAnimator()->AddAnimation(L"Cooldown_Completion", pAnimation);
	//	pGlobalEffect->GetAnimator()->Play(L"Cooldown_Completion");

	//	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	//	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	//	pGlobalEffect->GetTransform()->SetLocalPosition(Vec3(-63.f, 11.5f, -10.f));
	//	pGlobalEffect->GetTransform()->SetLocalScale(Vec3(24.f, 24.f, 1.f));

	//	AddGameObject(pGlobalEffect);
	//}

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
	//{
		//shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Compute");
		//shared_ptr<Texture> pTexture = make_shared<Texture>();
		//pTexture->Create(D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, 1024, 1024);

		//shared_ptr<Texture> pNoiseTexture = GET_SINGLE(Resources)->Load<Texture>(L"NoiseTexture", L"..\\Resources\\Texture\\Image_NoiseTexture.tga");
		//pMaterial->SetTexture(0, pTexture);
		//pMaterial->SetTexture(1, pNoiseTexture);
		//pMaterial->SetVec3(0, pNoiseTexture->GetTexSize());

		//pMaterial->Dispatch(1, 1024, 1);
		//GET_SINGLE(Resources)->Add<Texture>(L"ComputeTexture", pTexture);
	//}

	//Background
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Map\\Image_Town_Back.tga");
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		pMaterial->SetTexture(0, pTexture);
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<RigidBody>());
		pGameObject->AddComponent(make_shared<Movement>());
		pGameObject->AddComponent(make_shared<BackgroundMoveScript>(pPlayer));
		pGameObject->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(1.f, 1.f, 1.f)));
		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 800.f, fHeight / 2.f + 100.f, 140.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(2400.f, 350.f, 1.f));

		AddGameObject(pGameObject);
	}

	//Background_Bridge
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Map\\Image_Town_Bridge.tga");
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		pMaterial->SetTexture(0, pTexture);
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 800.f, fHeight / 2.f - 65.f, 130.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(2400.f, 400.f, 1.f));

		AddGameObject(pGameObject);
	}

	//Background_Surrounding
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Map\\Image_Town_Surrounding.tga");
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		pMaterial->SetTexture(0, pTexture);
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();

		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<PlayerTrackingScript>(pPlayer, 90.f));
		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 20.f, 90.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(680.f, 400.f, 1.f));

		AddGameObject(pGameObject);
	}


	// Camera
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		pGameObject->AddComponent(make_shared<CameraMoveScript>());
		pGameObject->AddComponent(make_shared<PlayerTrackingScript>(pPlayer));

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);

		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::HUD, true);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::UI, true);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::INTERFACE_EFFECT, true);
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
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::INTERFACE_EFFECT, false);
	}



	// NPC_Witch
	{
		shared_ptr<NPC_Witch> pWitch = make_shared<NPC_Witch>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
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
		shared_ptr<NPC_Wolf> pWolf = make_shared<NPC_Wolf>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pWolf->AddComponent(pMeshRenderer);
		pWolf->AddComponent(make_shared<Transform>());
		pWolf->AddComponent(make_shared<Physical>(ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::BOX, Vec3(217.f, 144.f, 1.f)));
		pWolf->AddComponent(make_shared<RigidBody>());
		pWolf->AddComponent(make_shared<Collider>());
		pWolf->AddComponent(make_shared<DebugRenderer>());
		pWolf->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Wolf_Idle", L"..\\Resources\\Animation\\Wolf\\wolf_idle.anim");
		pWolf->GetAnimator()->AddAnimation(L"Wolf_Idle", pAnimation);
		pWolf->GetAnimator()->Play(L"Wolf_Idle");

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pWolf->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 600.f, fHeight / 2.f - 80.f, 100.5f));

		AddGameObject(pWolf);
	}

	// NPC_Ogre
	{
		shared_ptr<NPC_Ogre> pOgre = make_shared<NPC_Ogre>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
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
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
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

	// Test HUD
	//{
	//	shared_ptr<HUD> pHUD = make_shared<HUD>();

	//	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	//	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	//	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(L"EffectTarget");
	//	pMaterial->SetTexture(0, pTexture);

	//	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	//	pMeshRenderer->SetMaterial(pMaterial);
	//	pMeshRenderer->SetMesh(pMesh);

	//	pHUD->AddComponent(pMeshRenderer);
	//	pHUD->AddComponent(make_shared<Transform>());
	//	pHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

	//	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	//	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	//	pHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 600.f, fHeight / 2.f, 10.f));
	//	pHUD->GetTransform()->SetLocalScale(Vec3(200.f, 112.f, 1.f));

	//	AddGameObject(pHUD);
	//}

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
