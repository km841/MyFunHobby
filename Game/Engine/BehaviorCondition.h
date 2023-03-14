#pragma once
#include "BehaviorNode.h"

// 특정 조건을 수행하고 결과를 반환한다.
// EX) 플레이어가 멀리 떨어져있다면? SUCCESS
class BehaviorCondition
	: public BehaviorNode
{
public:
	BehaviorCondition(std::function<bool()> fnCondition);
	virtual ~BehaviorCondition();

public:
	virtual BEHAVIOR_RESULT Run() override;

private:
	std::function<bool()> m_fnCondition;
};

