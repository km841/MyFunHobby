#include "pch.h"
#include "IsDeadCondition.h"

IsDeadCondition::IsDeadCondition(shared_ptr<GameObject> pGameObject)
	: BehaviorCondition(pGameObject)
{
}

IsDeadCondition::~IsDeadCondition()
{
}

BEHAVIOR_RESULT IsDeadCondition::Run()
{
	if (m_pGameObject.lock()->GetStatus()->IsAlive())
	{
		return BEHAVIOR_RESULT::FAILURE;
	}
	else
	{
		return BEHAVIOR_RESULT::SUCCESS;
	}
	return BEHAVIOR_RESULT::RUNNING;
}
