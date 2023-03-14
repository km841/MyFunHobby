#pragma once
#include "BehaviorNode.h"

// Ư�� �۾��� �����ϰ� ����� ��ȯ�Ѵ�
// EX) ���Ͱ� �÷��̾ �����Ѵ�
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

