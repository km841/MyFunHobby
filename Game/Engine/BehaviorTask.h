#pragma once
#include "BehaviorNode.h"
#include "GameObject.h"

// 특정 작업을 수행하고 결과를 반환한다
// EX) 몬스터가 플레이어를 공격한다
class GameObject;
class BehaviorTask
	: public BehaviorNode
{
public:
	BehaviorTask(shared_ptr<GameObject> pGameObject);
	virtual ~BehaviorTask() { }

public:
	virtual BEHAVIOR_RESULT Run() { return BEHAVIOR_RESULT::SUCCESS; }

protected:
	weak_ptr<GameObject> m_pGameObject;

};

