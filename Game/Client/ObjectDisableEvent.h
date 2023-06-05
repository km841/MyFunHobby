#pragma once
#include "DungeonEvent.h"
class GameObject;
class ObjectDisableEvent :
    public DungeonEvent
{
public:
	ObjectDisableEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<GameObject> pGameObject);
	virtual ~ObjectDisableEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	weak_ptr<GameObject> m_pGameObject;
};

