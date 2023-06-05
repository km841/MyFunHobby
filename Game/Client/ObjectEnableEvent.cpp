#include "pch.h"
#include "ObjectEnableEvent.h"
#include "GameObject.h"

ObjectEnableEvent::ObjectEnableEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<GameObject> pGameObject)
	: DungeonEvent(DUNGEON_EVENT_KIND::OBJECT_ENABLE, pConditionBlock)
	, m_pGameObject(pGameObject)
{
}

ObjectEnableEvent::~ObjectEnableEvent()
{
}

void ObjectEnableEvent::Update()
{
	DungeonEvent::Update();
}

void ObjectEnableEvent::ExecuteEvent()
{
	m_pGameObject.lock()->Enable();
}
