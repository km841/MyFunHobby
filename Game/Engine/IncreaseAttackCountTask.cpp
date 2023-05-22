#include "pch.h"
#include "IncreaseAttackCountTask.h"
#include "ErodedHeavyInfantry.h"

IncreaseAttackCountTask::IncreaseAttackCountTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT IncreaseAttackCountTask::Run()
{
	static_pointer_cast<ErodedHeavyInfantry>(m_pGameObject.lock())->IncreaseAttackCount();

	return BEHAVIOR_RESULT::SUCCESS;
}
