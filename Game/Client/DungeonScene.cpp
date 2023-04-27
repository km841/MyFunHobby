#include "pch.h"
#include "DungeonScene.h"
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
#include "SceneChangeEventObject.h"

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

DungeonScene::DungeonScene()
	: Scene(SCENE_TYPE::DUNGEON)
{
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Awake()
{
	Scene::Awake();
}

void DungeonScene::Start()
{
	Scene::Start();
}

void DungeonScene::Update()
{
	Scene::Update();
}

void DungeonScene::LateUpdate()
{
	Scene::LateUpdate();
}

void DungeonScene::FinalUpdate()
{
	Scene::FinalUpdate();
}

void DungeonScene::Render()
{
	Scene::Render();
}

void DungeonScene::Enter()
{
	Load(L"..\\Resources\\Map\\BaseCampMap.map");
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	// Create Monster
	{
		GET_SINGLE(ObjectFactory)->SetPlayer(GetPlayer().lock());
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f - 600.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f - 300.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 300.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 600.f, fHeight / 2.f - 200.f, 99.5f));
	}

	//Background
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		pGameObject->SetFrustum(false);
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Map\\Image_BaseCamp_Background.png");
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		pMaterial->SetTexture(0, pTexture);
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 300.f, 140.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1600.f, 900.f, 1.f));

		AddGameObject(pGameObject);
	}

	AwakeLocalObjects();
	RegisterSceneEvent(EVENT_TYPE::SCENE_FADE_EVENT, static_cast<uint8>(SCENE_FADE_EFFECT::FADE_IN), 1.f);
}

void DungeonScene::Exit()
{
}
