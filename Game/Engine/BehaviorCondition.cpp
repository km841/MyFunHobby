#include "pch.h"
#include "BehaviorCondition.h"

BehaviorCondition::BehaviorCondition(std::function<bool()> fnCondition)
	: m_fnCondition(fnCondition)
{
}

BehaviorCondition::~BehaviorCondition()
{
}

BEHAVIOR_RESULT BehaviorCondition::Run()
{
	return m_fnCondition() ? BEHAVIOR_RESULT::SUCCESS : BEHAVIOR_RESULT::FAILURE;
}
