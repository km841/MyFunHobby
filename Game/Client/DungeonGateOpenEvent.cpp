#include "pch.h"
#include "DungeonGateOpenEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "Animator.h"
#include "GameObject.h"
#include "DungeonGate.h"

DungeonGateOpenEvent::DungeonGateOpenEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::DUNGEON_GATE_OPEN, pConditionBlock)
{
}

DungeonGateOpenEvent::~DungeonGateOpenEvent()
{
}

void DungeonGateOpenEvent::Update()
{
	DungeonEvent::Update();
}

void DungeonGateOpenEvent::ExecuteEvent()
{
	auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::DUNGEON_GATE);
	for (auto& pGameObject : vGameObjects)
	{
		pGameObject->GetAnimator()->Play(L"DungeonGate_Activate");
		static_pointer_cast<DungeonGate>(pGameObject)->m_bOpen = true;
	}
}
