#pragma once
#include "DungeonEvent.h"
class PlayerWalkEvent :
    public DungeonEvent
{
public:
	PlayerWalkEvent(shared_ptr<ConditionBlock> pConditionBlock, const Vec3& vVelocity, float fDuration);
	virtual ~PlayerWalkEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	Vec3 m_vVelocity;
	float m_fDuration;
};

