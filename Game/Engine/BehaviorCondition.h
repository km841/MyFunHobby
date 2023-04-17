#pragma once
#include "BehaviorNode.h"

// 특정 조건을 수행하고 결과를 반환한다.
// EX) 플레이어가 멀리 떨어져있다면? SUCCESS
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

