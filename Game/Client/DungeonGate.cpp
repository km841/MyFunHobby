#include "pch.h"
#include "DungeonGate.h"
#include "Input.h"

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
			int a = 0;
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
