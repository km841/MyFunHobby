#include "pch.h"
#include "BehaviorCondition.h"

BehaviorCondition::BehaviorCondition(shared_ptr<GameObject> pGameObject)
	: m_pGameObject(pGameObject)
{
}

BehaviorCondition::~BehaviorCondition()
{
}
