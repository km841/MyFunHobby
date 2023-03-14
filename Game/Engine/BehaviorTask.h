#pragma once
#include "BehaviorNode.h"

// 특정 작업을 수행하고 결과를 반환한다
// EX) 몬스터가 플레이어를 공격한다
class BehaviorTask
	: public BehaviorNode
{
public:
	BehaviorTask(std::function<BEHAVIOR_RESULT()> fnTask);
	virtual ~BehaviorTask() { }

public:
	virtual BEHAVIOR_RESULT Run() override;

private:
	std::function<BEHAVIOR_RESULT()> m_fnTask;
};

