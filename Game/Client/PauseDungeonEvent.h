#pragma once
#include "DungeonEvent.h"
class PauseDungeonEvent :
    public DungeonEvent
{
public:
	PauseDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~PauseDungeonEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

