#pragma once
#include "BehaviorNode.h"

// Ư�� ������ �����ϰ� ����� ��ȯ�Ѵ�.
// EX) �÷��̾ �ָ� �������ִٸ�? SUCCESS
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

