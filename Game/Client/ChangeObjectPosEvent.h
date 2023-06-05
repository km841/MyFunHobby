#pragma once
#include "DungeonEvent.h"
class GameObject;
class ChangeObjectPosEvent :
    public DungeonEvent
{
public:
	ChangeObjectPosEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<GameObject> pGameObject, const Vec3& vNextPos);
	virtual ~ChangeObjectPosEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	weak_ptr<GameObject> m_pGameObject;
	Vec3 m_vNextPos;
};

