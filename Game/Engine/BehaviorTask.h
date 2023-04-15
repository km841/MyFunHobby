#pragma once
#include "BehaviorNode.h"
#include "GameObject.h"

// Ư�� �۾��� �����ϰ� ����� ��ȯ�Ѵ�
// EX) ���Ͱ� �÷��̾ �����Ѵ�
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

