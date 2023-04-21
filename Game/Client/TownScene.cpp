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
#include "InterfaceManager.h"
#include "Cemetery.h"
#include "ObjectFactory.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "NPC_Witch.h"
#include "NPC_Wolf.h"
#include "NPC_Wizard.h"
#include "NPC_Ogre.h"
#include "GlobalEffect.h"
#include "JuniorKnight.h"

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
#include "RigidBody.h"
#include "Collider.h"
#include "Physical.h"
#include "DebugRenderer.h"
#include "Animator.h"
#include "Movement.h"
#include "Light.h"
#include "AI.h"
#include "ParticleSystem.h"

/* Behavior Component */
#include "IsPlayerNearCondition.h"
#include "BehaviorTask.h"
#include "Sequence.h"
#include "MoveTask.h"
#include "RunAnimateTask.h"
#include "Selector.h"
#include "DelayTask.h"
#include "IsHitCondition.h"
#include "IsDeadCondition.h"
#include "RemoveObjectTask.h"


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
	shared_ptr<Player> pPlayer = nullptr;
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	Load(L"..\\Resources\\Map\\DefaultMap6.map");
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::PLAYER_PROJECTILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);

	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::TILE, LAYER_TYPE::PLAYER_PROJECTILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::TILE, LAYER_TYPE::MONSTER);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::TILE, LAYER_TYPE::PARTICLE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PARTICLE, LAYER_TYPE::PARTICLE);

	// Directional Light
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Light>());
		pGameObject->GetLight()->SetLightDirection(Vec3(0.f, 0.f, 1.f));
		pGameObject->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		pGameObject->GetLight()->SetDiffuse(Vec3(0.7f, 0.7f, 0.7f));
		pGameObject->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));

		AddGameObject(pGameObject);
	}

	
	// Player
	{
		pPlayer = make_shared<Player>();
		pPlayer->AddComponent(make_shared<Transform>());
		pPlayer->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(30.f, 30.f, 1.f)));
		pPlayer->AddComponent(make_shared<PlayerMoveScript>());
		pPlayer->AddComponent(make_shared<RigidBody>(true));
		pPlayer->AddComponent(make_shared<Collider>());
		pPlayer->AddComponent(make_shared<DebugRenderer>());
		pPlayer->AddComponent(make_shared<Movement>());
		pPlayer->ObtainSkul(GET_SINGLE(Cemetery)->Get(SKUL_TYPE::LITTLE_BONE));
		pPlayer->ObtainSkul(GET_SINGLE(Cemetery)->Get(SKUL_TYPE::HIGH_WARLOCK));

		pPlayer->AddComponent(make_shared<Light>());
		pPlayer->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
		pPlayer->GetLight()->SetLightRange(800.f);
		pPlayer->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		pPlayer->GetLight()->SetDiffuse(Vec3(1.f, 1.f, 1.f));

		pPlayer->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f + 100.f, 100.f));

		pPlayer->SetFrustum(false);
		AddGameObject(pPlayer);
	}

	// Create Monster
	{
		GET_SINGLE(ObjectFactory)->SetPlayer(pPlayer);
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 300.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 400.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 500.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 600.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 700.f, fHeight / 2.f - 200.f, 99.5f));
	}

	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_HEALTH_BAR)->SetPlayer(pPlayer);
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_FIRST)->SetPlayer(pPlayer);
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKUL_THUMNAIL)->SetPlayer(pPlayer);

	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_INTERFACE));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_HEALTH_BAR));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_FIRST));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKUL_THUMNAIL));

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
	//{
	//	shared_ptr<GameObject> pGround = make_shared<GameObject>(LAYER_TYPE::TILE);
	//	pGround->AddComponent(make_shared<Transform>());
	//	pGround->AddComponent(make_shared<Physical>(ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(2400.f, 400.f, 1.f)));
	//	pGround->AddComponent(make_shared<Collider>());
	//	pGround->AddComponent(make_shared<DebugRenderer>());

	//	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	//	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	//	pGround->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 800.f, fHeight / 2.f - 700.f, 100.f));
	//	pGround->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));

	//	AddGameObject(pGround);
	//}

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
		//shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		//pGameObject->SetFrustum(false);
		//shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		//shared_ptr<Texture> pTexture = make_shared<Texture>();
		//pTexture->Load(L"..\\Resources\\Texture\\Map\\Image_Town_Back.tga");
		//shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		//pMaterial->SetTexture(0, pTexture);
		//shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		//pMeshRenderer->SetMaterial(pMaterial);
		//pMeshRenderer->SetMesh(pMesh);
		//pGameObject->AddComponent(pMeshRenderer);
		//pGameObject->AddComponent(make_shared<Transform>());

		//pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 800.f, fHeight / 2.f + 100.f, 140.f));
		//pGameObject->GetTransform()->SetLocalScale(Vec3(2400.f, 350.f, 1.f));

		//AddGameObject(pGameObject);
	}

	//Background_Bridge
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		pGameObject->SetFrustum(false);
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

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 800.f, fHeight / 2.f - 65.f, 130.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(2400.f, 400.f, 1.f));

		AddGameObject(pGameObject);
	}

	//Background_Surrounding
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		pGameObject->SetFrustum(false);
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Map\\Image_Town_Surrounding.tga");
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		pMaterial->SetTexture(0, pTexture);
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();

		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());

		pGameObject->AddComponent(make_shared<PlayerTrackingScript>(pPlayer, 90.f));

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 500.f, fHeight / 2.f - 20.f, 90.f));
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
		shared_ptr<NPC_Witch> pWitch = GET_SINGLE(ObjectFactory)->CreateObject<NPC_Witch>(L"Deferred", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(400.f, 120.f, 1.f));
		pWitch->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Witch_Idle", L"..\\Resources\\Animation\\Witch\\witch_idle.anim");
		pWitch->GetAnimator()->AddAnimation(L"Witch_Idle", pAnimation);
		pWitch->GetAnimator()->Play(L"Witch_Idle");

		pWitch->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 300.f, fHeight / 2.f - 115.f, 110.f));
		AddGameObject(pWitch);
	}

	// NPC_Wolf
	{
		shared_ptr<NPC_Wolf> pWolf = GET_SINGLE(ObjectFactory)->CreateObject<NPC_Wolf>(L"Deferred", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(217.f, 144.f, 1.f));
		pWolf->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Wolf_Idle", L"..\\Resources\\Animation\\Wolf\\wolf_idle.anim");
		pWolf->GetAnimator()->AddAnimation(L"Wolf_Idle", pAnimation);
		pWolf->GetAnimator()->Play(L"Wolf_Idle");

		pWolf->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 600.f, fHeight / 2.f - 80.f, 100.5f));

		AddGameObject(pWolf);
	}

	// NPC_Ogre
	{
		shared_ptr<NPC_Ogre> pOgre = GET_SINGLE(ObjectFactory)->CreateObject<NPC_Ogre>(L"Deferred", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(227.f, 151.f, 1.f));
		pOgre->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Ogre_Idle", L"..\\Resources\\Animation\\Ogre\\ogre_idle.anim");
		pOgre->GetAnimator()->AddAnimation(L"Ogre_Idle", pAnimation);
		pOgre->GetAnimator()->Play(L"Ogre_Idle");

		pOgre->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 1200.f, fHeight / 2.f - 70.f, 110.f));

		AddGameObject(pOgre);
	}

	// NPC_Wizard
	{
		shared_ptr<NPC_Wizard> pWizard = GET_SINGLE(ObjectFactory)->CreateObject<NPC_Wizard>(L"Deferred", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(221.f, 151.f, 1.f));
		pWizard->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Wizard_Idle", L"..\\Resources\\Animation\\Wizard\\wizard_idle.anim");
		pWizard->GetAnimator()->AddAnimation(L"Wizard_Idle", pAnimation);
		pWizard->GetAnimator()->Play(L"Wizard_Idle");

		pWizard->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 2000.f, fHeight / 2.f - 70.f, 110.f));

		AddGameObject(pWizard);
	}

	// Test HUD
	//{
	//	shared_ptr<HUD> pHUD = make_shared<HUD>();

	//	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	//	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	//	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(L"PositionTarget");
	//	pMaterial->SetTexture(0, pTexture);

	//	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	//	pMeshRenderer->SetMaterial(pMaterial);
	//	pMeshRenderer->SetMesh(pMesh);

	//	pHUD->AddComponent(pMeshRenderer);
	//	pHUD->AddComponent(make_shared<Transform>());
	//	//pHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

	//	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	//	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	//	pHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 10.f));
	//	pHUD->GetTransform()->SetLocalScale(Vec3(800, 450, 1.f));

	//	AddGameObject(pHUD);
	//}

	//// Test HUD
	//{
	//	shared_ptr<HUD> pHUD = make_shared<HUD>();

	//	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	//	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	//	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(L"DiffuseLightTarget");
	//	pMaterial->SetTexture(0, pTexture);

	//	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	//	pMeshRenderer->SetMaterial(pMaterial);
	//	pMeshRenderer->SetMesh(pMesh);

	//	pHUD->AddComponent(pMeshRenderer);
	//	pHUD->AddComponent(make_shared<Transform>());
	//	//pHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

	//	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	//	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	//	pHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 200.f, fHeight / 2.f + 200.f, 10.f));
	//	pHUD->GetTransform()->SetLocalScale(Vec3(200.f, 112.f, 1.f));

	//	AddGameObject(pHUD);
	//}

	// Particle System
	{
		shared_ptr<GameObject> pParticle = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		pParticle->AddComponent(make_shared<Transform>());
		pParticle->AddComponent(make_shared<ParticleSystem>());
		pParticle->SetFrustum(false);
		pParticle->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 60.f));
		pParticle->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 1.f));
		AddGameObject(pParticle);
	}



	AddGameObject(GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DIALOGUE));
	GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DIALOGUE)->Disable();
	
	// Fade In/Out Object
	{
		shared_ptr<UI> pUI = make_shared<UI>();
		pUI->SetFrustum(false);
		pUI->AddComponent(make_shared<Transform>());

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"FadeInOut");

		auto [vVertices, vIndices] = Vertex::CreateBoxVerticesAndIndicesTri(Vec3(1.f, 1.f, 1.f));
		shared_ptr<Mesh> pMesh = make_shared<Mesh>();

		pMesh->Init(vVertices, vIndices);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pUI->AddComponent(pMeshRenderer);

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
