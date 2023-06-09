#include "pch.h"
#include "DungeonGate.h"
#include "Input.h"
#include "EventManager.h"
#include "SceneChangeEvent.h"
#include "Player.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "Engine.h"
#include "RigidBody.h"
#include "ComponentObject.h"
#include "GoToNextDungeonEvent.h"
#include "DungeonScene.h"
#include "ObjectFactory.h"
#include "LocalEffect.h"

DungeonGate::DungeonGate(STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType)
	: GameObject(LAYER_TYPE::DUNGEON_GATE)
	, m_eStageKind(eStageKind)
	, m_eDungeonType(eDungeonType)
	, m_bIsCollisionWithPlayer(false)
	, m_bOpen(false)
{
}

DungeonGate::~DungeonGate()
{
}

void DungeonGate::Awake()
{
	GameObject::Awake();
	CreateKeyEffectAndAddedToScene();
}

void DungeonGate::Start()
{
	GameObject::Start();
}

void DungeonGate::Update()
{
	GameObject::Update();

	if (m_bOpen && m_bIsCollisionWithPlayer)
	{
		Vec3 vPos = GetTransform()->GetPhysicalPosition();
		vPos.y -= 130.f;
		FONT->DrawStringAtWorldPos(L"����", 20.f, vPos, FONT_WEIGHT::BOLD);

		m_pHoveringKeyEffect->Enable();
		if (IS_DOWN(KEY_TYPE::F))
		{
			SCENE_TYPE eSceneType=GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			if (SCENE_TYPE::DUNGEON != eSceneType)
				return;

			weak_ptr<Stage> pStage = static_pointer_cast<DungeonScene>(GET_SINGLE(Scenes)->GetActiveScene())->GetActiveStage();
			GET_SINGLE(EventManager)->AddEvent(make_unique<GoToNextDungeonEvent>(pStage.lock(), m_eDungeonType));
		}
	}
	else
	{
		m_pHoveringKeyEffect->Disable();
	}
}

void DungeonGate::LateUpdate()
{
	GameObject::LateUpdate();
}

void DungeonGate::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void DungeonGate::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = true;
	}
}

void DungeonGate::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = false;
	}
}

void DungeonGate::CreateKeyEffectAndAddedToScene()
{
	m_pHoveringKeyEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LocalEffect>(
		L"Forward", L"..\\Resources\\Texture\\Key\\Image_Key_F.png");

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.x -= 55.f;
	vPos.y -= 140.f;
	vPos.z -= 5.f;

	m_pHoveringKeyEffect->GetTransform()->SetLocalPosition(vPos);
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pHoveringKeyEffect, SCENE_TYPE::DUNGEON));
}
