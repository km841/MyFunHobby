#include "pch.h"
#include "DelayTask.h"
#include "Clock.h"
#include "Monster.h"

DelayTask::DelayTask(shared_ptr<GameObject> pGameObject, float fDuration)
	: BehaviorTask(pGameObject)
	, m_tDuration(fDuration)
	, m_bHitFlag(false)
{
}

BEHAVIOR_RESULT DelayTask::Run()
{
	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(m_pGameObject.lock());

	if (!m_bHitFlag && pMonster.lock()->IsHitFlag())
	{
		m_tDuration.Start();
		m_bHitFlag = true;
	}


	if (pMonster.lock()->IsHitFlag())
	{
		if (pMonster.lock()->IsExtraHitFlag())
		{
			m_tDuration.Start();
		}
		pMonster.lock()->UnflagAsExtraAttacked();
	}
	

	if (m_tDuration.IsRunning())
	{
		m_tDuration.Update(DELTA_TIME);
	}

	if (m_bHitFlag && m_tDuration.IsFinished())
	{
		pMonster.lock()->UnflagAsAttacked();
		m_bHitFlag = false;
	}

	return BEHAVIOR_RESULT::SUCCESS;
}
