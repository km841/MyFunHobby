#include "pch.h"
#include "TimerCondition.h"
#include "Clock.h"

TimerCondition::TimerCondition(shared_ptr<GameObject> pGameObject, float fDuration)
	: BehaviorCondition(pGameObject)
	, m_tDuration(fDuration)
{
}

BEHAVIOR_RESULT TimerCondition::Run()
{
	if (!m_tDuration.IsRunning() || m_tDuration.IsFinished())
		m_tDuration.Start();

	m_tDuration.Update(OBJECT_DELTA_TIME);

	if (m_tDuration.IsFinished())
		return BEHAVIOR_RESULT::SUCCESS;

	return BEHAVIOR_RESULT::FAILURE;
}
