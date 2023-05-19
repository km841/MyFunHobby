#include "pch.h"
#include "UnflagAsAttackedFlagTask.h"
#include "Monster.h"

UnflagAsAttackedFlagTask::UnflagAsAttackedFlagTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT UnflagAsAttackedFlagTask::Run()
{
	static_pointer_cast<Monster>(m_pGameObject.lock())->UnflagAsAttacked();
	static_pointer_cast<Monster>(m_pGameObject.lock())->UnflagAsExtraAttacked();

	return BEHAVIOR_RESULT::SUCCESS;
}
