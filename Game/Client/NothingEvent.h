#pragma once
#include "DungeonEvent.h"
class NothingEvent :
    public DungeonEvent
{
public:
	NothingEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~NothingEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

