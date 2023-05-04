#include "pch.h"
#include "DungeonGate.h"

DungeonGate::DungeonGate()
{
}

DungeonGate::~DungeonGate()
{
}

void DungeonGate::Awake()
{
	EventObject::Awake();
}

void DungeonGate::Start()
{
	EventObject::Start();
}

void DungeonGate::Update()
{
	EventObject::Update();
}

void DungeonGate::LateUpdate()
{
	EventObject::LateUpdate();
}

void DungeonGate::FinalUpdate()
{
	EventObject::FinalUpdate();
}

void DungeonGate::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
	}
}

void DungeonGate::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
	}
}
