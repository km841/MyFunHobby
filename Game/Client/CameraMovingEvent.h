#pragma once
#include "DungeonEvent.h"
class CameraMovingEvent :
    public DungeonEvent
{
public:
	CameraMovingEvent(shared_ptr<ConditionBlock> pConditionBlock, const Vec3& vTargetPos, float fTime);
	virtual ~CameraMovingEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	Vec3 m_vTargetPos;
	float m_fTime;
};

