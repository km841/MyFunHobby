#pragma once
#include "DungeonEvent.h"
class StopBGMEvent :
    public DungeonEvent
{
public:
	StopBGMEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~StopBGMEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

