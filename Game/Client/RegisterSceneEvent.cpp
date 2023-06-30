#include "pch.h"
#include "RegisterSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"

RegisterSceneEvent::RegisterSceneEvent(shared_ptr<ConditionBlock> pConditionBlock, EVENT_TYPE eEventType, float fDuration)
	: DungeonEvent(DUNGEON_EVENT_KIND::REGISTER_SCENE_EVENT, pConditionBlock)
	, m_eEventType(eEventType)
	, m_fDuration(fDuration)
{
}

RegisterSceneEvent::~RegisterSceneEvent()
{
}

void RegisterSceneEvent::Update()
{
	DungeonEvent::Update();
}

void RegisterSceneEvent::ExecuteEvent()
{
	GET_SINGLE(Scenes)->GetActiveScene()->RegisterSceneEvent(m_eEventType, 0, m_fDuration);
}
