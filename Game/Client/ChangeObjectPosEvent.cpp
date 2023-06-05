#include "pch.h"
#include "ChangeObjectPosEvent.h"
#include "GameObject.h"
#include "Transform.h"

ChangeObjectPosEvent::ChangeObjectPosEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<GameObject> pGameObject, const Vec3& vNextPos)
	: DungeonEvent(DUNGEON_EVENT_KIND::CHANGE_OBJECT_POS, pConditionBlock)
	, m_pGameObject(pGameObject)
	, m_vNextPos(vNextPos)
{
}

ChangeObjectPosEvent::~ChangeObjectPosEvent()
{
}

void ChangeObjectPosEvent::Update()
{
	DungeonEvent::Update();
}

void ChangeObjectPosEvent::ExecuteEvent()
{
	m_pGameObject.lock()->GetTransform()->SetLocalPosition(m_vNextPos);
}
