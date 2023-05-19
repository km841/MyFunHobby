#include "pch.h"
#include "DeadEventTriggerTask.h"
#include "Monster.h"

DeadEventTriggerTask::DeadEventTriggerTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_bTrigger(false)
{
}

BEHAVIOR_RESULT DeadEventTriggerTask::Run()
{
	if (!m_bTrigger)
	{
		shared_ptr<Monster> pMonster = static_pointer_cast<Monster>(m_pGameObject.lock());
		pMonster->ActivateDeadEvent();
		m_bTrigger = true;
	}

	return BEHAVIOR_RESULT::SUCCESS;
}
