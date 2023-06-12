#pragma once
#include "DungeonEvent.h"
class CameraFixedEvent :
    public DungeonEvent
{
public:
	CameraFixedEvent(shared_ptr<ConditionBlock> pConditionBlock, const Vec3& vFixedPos);
	virtual ~CameraFixedEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	Vec3 m_vFixedPos;
};

