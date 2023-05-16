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
#include "PlayerSkillShowScript.h"
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
#include "ComponentObject.h"

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

/* Stage */
#include "BlackLab.h"
#include "CitadelOfFate.h"

DungeonScene::DungeonScene()
	: Scene(SCENE_TYPE::DUNGEON)
{
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Awake()
{
	m_arrStages[static_cast<uint8>(STAGE_KIND::BLACK_LAB)] = make_shared<BlackLab>();
	m_arrStages[static_cast<uint8>(STAGE_KIND::CITADEL_OF_FATE)] = make_shared<CitadelOfFate>();

	m_pActiveStage = m_arrStages[static_cast<uint8>(STAGE_KIND::BLACK_LAB)];
	m_pActiveStage.lock()->Enter();

	AwakeLocalObjects();
}

void DungeonScene::Start()
{
	Scene::Start();
	m_pActiveStage.lock()->Start();
}

void DungeonScene::Update()
{
	Scene::Update();
	m_pActiveStage.lock()->Update();
}

void DungeonScene::LateUpdate()
{
	Scene::LateUpdate();
	m_pActiveStage.lock()->LateUpdate();
}

void DungeonScene::FinalUpdate()
{
	Scene::FinalUpdate();
	m_pActiveStage.lock()->FinalUpdate();
}

void DungeonScene::Render()
{
	Scene::Render();
}

void DungeonScene::Enter()
{
	InitializeCameraAndPlayerPos();
	Awake();
}

void DungeonScene::Exit()
{
	m_pActiveStage.lock()->Exit();
}

void DungeonScene::InitializeCameraAndPlayerPos()
{
	weak_ptr<Player> pPlayer = GetPlayer();

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());
	pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	pPlayer.lock()->GetTransform()->SetPhysicalPosition(Vec3(-1400.f, fHeight / 2.f + 200.f, 100.f));
	GetMainCamera().lock()->GetTransform()->SetLocalPosition(Vec3(-1400.f, fHeight / 2.f + 500.f, 1.f));
}
