#pragma once
#include "BehaviorNode.h"

// Ư�� ������ �����ϰ� ����� ��ȯ�Ѵ�.
// EX) �÷��̾ �ָ� �������ִٸ�? SUCCESS
#include "GameObject.h"

class BehaviorCondition
	: public BehaviorNode
{
public:
	BehaviorCondition(shared_ptr<GameObject> pGameObject);
	virtual ~BehaviorCondition();

public:
	virtual BEHAVIOR_RESULT Run() { return BEHAVIOR_RESULT::SUCCESS; }

protected:
	weak_ptr<GameObject> m_pGameObject;
};

