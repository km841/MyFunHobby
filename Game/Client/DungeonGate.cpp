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

DungeonGate::DungeonGate(STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType)
	: GameObject(LAYER_TYPE::DUNGEON_GATE)
	, m_eStageKind(eStageKind)
	, m_eDungeonType(eDungeonType)
	, m_bIsCollisionWithPlayer(false)
{
}

DungeonGate::~DungeonGate()
{
}

void DungeonGate::Awake()
{
	GameObject::Awake();
}

void DungeonGate::Start()
{
	GameObject::Start();
}

void DungeonGate::Update()
{
	GameObject::Update();

	if (m_bIsCollisionWithPlayer)
	{
		if (IS_DOWN(KEY_TYPE::F))
		{
			switch (m_eDungeonType)
			{
			case DUNGEON_TYPE::BASE_CAMP:
				break;
			case DUNGEON_TYPE::DUNGEON_ITEM:
				break;
			case DUNGEON_TYPE::DUNGEON_GOLD:
				break;
			case DUNGEON_TYPE::DUNGEON_BONE:
				break;
			case DUNGEON_TYPE::VICE_BOSS:
				break;
			case DUNGEON_TYPE::STAGE_BOSS:
				break;
			case DUNGEON_TYPE::SHOP:
			{
				GET_SINGLE(EventManager)->AddEvent(make_unique<SceneChangeEvent>(SCENE_TYPE::SHOP));
			}

				break;
			}
		}
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
