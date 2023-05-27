#include "pch.h"
#include "TownScene.h"
#include "Engine.h"


/* Event */
#include "SceneChangeEvent.h"
#include "SceneFadeEvent.h"

/* Interface */
#include "PlayerInterfaceHUD.h"
#include "HealthBarHUD.h"
#include "SkulThumnailHUD.h"
#include "DialogueUI.h"
#include "SkillBoxHUD.h"

/* Script */
#include "PlayerHealthBarShowScript.h"
#include "PlayerTrackingScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "PlayerSkillShowScript.h"
#include "GlobalEffectSettingScript.h"
#include "PlayerSkulThumnailScript.h"
#include "PlayerFunctionScript.h"
#include "BGCameraScript.h"
#include "DarkMirrorReflectionScript.h"
#include "BackgroundMoveScript.h"

/* Manager */
#include "Resources.h"
#include "Input.h"
#include "CollisionManager.h"
#include "InterfaceManager.h"
#include "Cemetery.h"
#include "ObjectFactory.h"
#include "ComponentObject.h"

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
#include "SceneChangeEventObject.h"
#include "Background.h"
#include "DungeonGate.h"
#include "DarkMirror.h"
#include "Ch3BeginTower.h"
#include "DecoObject.h"
#include "DropEssence.h"

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

/* Items */
#include "ForbiddenSword.h"
#include "EvilSwordKirion.h"

/* Essence */
#include "Lyweasel.h"


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
	ShowCursor(false);
	shared_ptr<Player> pPlayer = nullptr;
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	Load(L"..\\Resources\\Map\\DefaultMap.map");
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::EVENT_OBJECT);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::DUNGEON_GATE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::DROP_ESSENCE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER, LAYER_TYPE::MAP_REWARD);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PLAYER_PROJECTILE, LAYER_TYPE::MONSTER);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::POSSESSION, LAYER_TYPE::MONSTER);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::POSSESSION, LAYER_TYPE::TILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::DROPING_REWARDS, LAYER_TYPE::TILE);

	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::TILE, LAYER_TYPE::PLAYER_PROJECTILE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::TILE, LAYER_TYPE::MONSTER);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::TILE, LAYER_TYPE::PARTICLE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::PARTICLE, LAYER_TYPE::PARTICLE);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LAYER_TYPE::MONSTER, LAYER_TYPE::PLAYER_PROJECTILE);

	// Far Clouds
	{
		shared_ptr<Background> pClouds = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Background>(
			L"Deferred", L"..\\Resources\\Texture\\Map\\Image_Town_Background_Cloud2.png");

		pClouds->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 400.f, fHeight / 2.f - 600.f, 195.f));
		pClouds->SetFollowSpeed(Vec3(4.f, 4.f, 1.f));

		pClouds->SetFrustum(false);
		AddGameObject(pClouds);
	}

	// Clouds
	{
		shared_ptr<Background> pClouds = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Background>(
			L"Deferred", L"..\\Resources\\Texture\\Map\\Image_Town_Background_Cloud.png");

		pClouds->AddComponent(make_shared<BackgroundMoveScript>(-50.f));

		pClouds->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 190.f));
		pClouds->SetFollowSpeed(Vec3(8.f, 8.f, 1.f));
		
		pClouds->SetFrustum(false);
		AddGameObject(pClouds);
	}

	// Clouds
	{
		shared_ptr<Background> pClouds = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Background>(
			L"Deferred", L"..\\Resources\\Texture\\Map\\Image_Town_Background_Cloud.png");

		pClouds->AddComponent(make_shared<BackgroundMoveScript>(-50.f));

		pClouds->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 3000.f, fHeight / 2.f, 190.f));
		pClouds->SetFollowSpeed(Vec3(8.f, 8.f, 1.f));

		pClouds->SetFrustum(false);
		AddGameObject(pClouds);
	}
	
	// Player
	{
		pPlayer = make_shared<Player>();
		GET_SINGLE(ObjectFactory)->SetPlayer(pPlayer);

		pPlayer->AddComponent(make_shared<Transform>());
		pPlayer->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(30.f, 30.f, 1.f)));
		pPlayer->AddComponent(make_shared<PlayerMoveScript>());
		pPlayer->AddComponent(make_shared<PlayerFunctionScript>());
		pPlayer->AddComponent(make_shared<RigidBody>(true));
		pPlayer->AddComponent(make_shared<Collider>());
		pPlayer->AddComponent(make_shared<DebugRenderer>());
		pPlayer->AddComponent(make_shared<Movement>());
		pPlayer->ObtainSkul(GET_SINGLE(Cemetery)->Get(SKUL_KIND::LITTLE_BONE));
		pPlayer->ObtainSkul(GET_SINGLE(Cemetery)->Get(SKUL_KIND::HIGH_WARLOCK));
		pPlayer->ObtainItem(GET_SINGLE(ObjectFactory)->CreateItem<ForbiddenSword>());
		pPlayer->ObtainItem(GET_SINGLE(ObjectFactory)->CreateItem<EvilSwordKirion>());

		pPlayer->AddComponent(make_shared<Light>());
		pPlayer->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
		pPlayer->GetLight()->SetLightRange(350.f);
		pPlayer->GetLight()->SetDiffuse(Vec3(0.6f, 0.6f, 0.6f));

		pPlayer->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 150.f, 98.f));

		pPlayer->SetFrustum(false);
		AddGameObject(pPlayer);
	}

	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_HEALTH_BAR)->SetPlayer(pPlayer);
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_FIRST)->SetPlayer(pPlayer);
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_SECOND)->SetPlayer(pPlayer);
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKUL_THUMNAIL)->SetPlayer(pPlayer);

	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_INTERFACE));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_HEALTH_BAR));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SECOND_SKILL_FRAME));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_FIRST));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_SECOND));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKUL_THUMNAIL));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_HIT));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::MOUSE_POINTER));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(UI_TYPE::INVENTORY));
	AddGameObject(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BASECAMP_OPENING));

	//Scene Change Event Object
	{
		shared_ptr<SceneChangeEventObject> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<SceneChangeEventObject>(
			L"Deferred", false, ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(500.f, 100.f, 1.f), MassProperties(), L"", pPlayer);
		
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 1850.f, fHeight / 2.f - 3000.f, 100.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1000.f, 100.f, 1.f));

		AddGameObject(pGameObject);
	}

	// Connect the player to the camera! 
	{
		GetMainCamera().lock()->AddComponent(make_shared<PlayerTrackingScript>(pPlayer));
	}

	// Black Mirror
	{
		shared_ptr<GameObject> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(
			L"Forward", L"..\\Resources\\Texture\\DecoObject\\Image_DarkMirrorFrame.png", LAYER_TYPE::UNKNOWN);

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 160.f, 100.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(105.f, 120.f, 1.f));

		AddGameObject(pGameObject);
	}

	//Test HUD
	{
		//shared_ptr<HUD> pHUD = make_shared<HUD>();

		//shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		//shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		//shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(L"AccumulatedLight");
		//pMaterial->SetTexture(0, pTexture);

		//shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		//pMeshRenderer->SetMaterial(pMaterial);
		//pMeshRenderer->SetMesh(pMesh);

		//pHUD->AddComponent(pMeshRenderer);
		//pHUD->AddComponent(make_shared<Transform>());
		////pHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		////float fWidth = static_cast<float>(g_pEngine->GetWidth());
		////float fHeight = static_cast<float>(g_pEngine->GetHeight());

		//pHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f + 200.f, 10.f));
		//pHUD->GetTransform()->SetLocalScale(Vec3(442, 260, 1.f));

		//AddGameObject(pHUD);
	}
	
	//ActivateDistortion(3.f);

	//RegisterSceneEvent(EVENT_TYPE::SCENE_FADE_EVENT, static_cast<uint8>(SCENE_FADE_EFFECT::FADE_IN), 1.f);
	RegisterSceneEvent(EVENT_TYPE::ACTIVATE_DISTORTION, 0, 1.f);
	RegisterSceneEvent(EVENT_TYPE::ACTIVATE_AFTEREFFECT, 0, 3.f);

	AddGameObject(GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DIALOGUE));
	GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DIALOGUE)->Disable();

	// GameObject를 깨우는 작업
	Awake();
}

void TownScene::Exit()
{
	// 모든 Actor를 씬에서 제거한다.
	GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::TILE);
	GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::BACKGROUND);

}
