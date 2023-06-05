#pragma once
#include "DungeonEvent.h"
class EnablePlayerHUDEvent :
    public DungeonEvent
{
public:
	EnablePlayerHUDEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~EnablePlayerHUDEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

