#include "pch.h"
#include "TokenStateChangeTask.h"
#include "ConditionToken.h"

TokenStateChangeTask::TokenStateChangeTask(shared_ptr<GameObject> pGameObject, shared_ptr<ConditionToken> pToken, bool bSetState)
	: BehaviorTask(pGameObject)
	, m_pToken(pToken)
	, m_bState(bSetState)
{
}

TokenStateChangeTask::~TokenStateChangeTask()
{
}

BEHAVIOR_RESULT TokenStateChangeTask::Run()
{
	m_pToken->SetState(m_bState);
	return BEHAVIOR_RESULT::SUCCESS;
}
