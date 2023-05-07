#pragma once
#include "DungeonEvent.h"
class PlayerTeleportEvent :
    public DungeonEvent
{
public:
	PlayerTeleportEvent(shared_ptr<ConditionBlock> pConditionBlock, const Vec3& vPlayerPos);
	virtual ~PlayerTeleportEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	Vec3 m_vDescPos;
};

