#include "pch.h"
#include "IsTokenStateCondition.h"
#include "ConditionToken.h"

IsTokenStateCondition::IsTokenStateCondition(shared_ptr<GameObject> pGameObject, shared_ptr<ConditionToken> pToken, bool bSelectState)
	: BehaviorCondition(pGameObject)
	, m_pToken(pToken)
	, m_bState(bSelectState)
{
}

IsTokenStateCondition::~IsTokenStateCondition()
{
}

BEHAVIOR_RESULT IsTokenStateCondition::Run()
{
	if (m_pToken->GetState() == m_bState)
		return BEHAVIOR_RESULT::SUCCESS;
	else
		return BEHAVIOR_RESULT::FAILURE;
}
