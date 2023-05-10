#pragma once
#include "DungeonEvent.h"
class DungeonGateOpenEvent :
    public DungeonEvent
{
public:
	DungeonGateOpenEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~DungeonGateOpenEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

