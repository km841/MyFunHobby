#include "pch.h"
#include "ObjectDisableEvent.h"
#include "GameObject.h"

ObjectDisableEvent::ObjectDisableEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<GameObject> pGameObject)
	: DungeonEvent(DUNGEON_EVENT_KIND::OBJECT_DISABLE, pConditionBlock)
	, m_pGameObject(pGameObject)
{
}

ObjectDisableEvent::~ObjectDisableEvent()
{
}

void ObjectDisableEvent::Update()
{
	DungeonEvent::Update();
}

void ObjectDisableEvent::ExecuteEvent()
{
	m_pGameObject.lock()->Disable();
}
