#include "pch.h"
#include "IsFinishedRageAttackCondition.h"
#include "ErodedHeavyInfantry.h"

IsFinishedRageAttackCondition::IsFinishedRageAttackCondition(shared_ptr<GameObject> pGameObject, int32 iAttackCount)
	: BehaviorCondition(pGameObject)
	, m_iAttackCount(iAttackCount)
{
}

IsFinishedRageAttackCondition::~IsFinishedRageAttackCondition()
{
}

BEHAVIOR_RESULT IsFinishedRageAttackCondition::Run()
{
	int32 iAttackCount = static_pointer_cast<ErodedHeavyInfantry>(m_pGameObject.lock())->GetAttackCount();
	if (m_iAttackCount <= iAttackCount)
		return BEHAVIOR_RESULT::SUCCESS;

	else
	{
		//static_pointer_cast<ErodedHeavyInfantry>(m_pGameObject.lock())->IncreaseAttackCount();
		return BEHAVIOR_RESULT::FAILURE;
	}
}
