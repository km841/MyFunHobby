#include "pch.h"
#include "SceneChangeDungeonEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "EventManager.h"
#include "SceneChangeEvent.h"

SceneChangeDungeonEvent::SceneChangeDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock, SCENE_TYPE eSceneType)
	: DungeonEvent(DUNGEON_EVENT_KIND::SCENE_CHANGE_EVENT, pConditionBlock)
	, m_eSceneType(eSceneType)
{
}

SceneChangeDungeonEvent::~SceneChangeDungeonEvent()
{
}

void SceneChangeDungeonEvent::Update()
{
	DungeonEvent::Update();
}

void SceneChangeDungeonEvent::ExecuteEvent()
{
	GET_SINGLE(EventManager)->AddEvent(make_unique<SceneChangeEvent>(m_eSceneType));
}
