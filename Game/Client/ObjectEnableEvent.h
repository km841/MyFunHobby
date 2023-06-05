#pragma once
#include "DungeonEvent.h"
class GameObject;
class ObjectEnableEvent :
    public DungeonEvent
{
public:
	ObjectEnableEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<GameObject> pGameObject);
	virtual ~ObjectEnableEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	weak_ptr<GameObject> m_pGameObject;
};

