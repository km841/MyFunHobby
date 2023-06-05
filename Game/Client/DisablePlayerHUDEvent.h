#pragma once
#include "DungeonEvent.h"
class DisablePlayerHUDEvent :
    public DungeonEvent
{
public:
	DisablePlayerHUDEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~DisablePlayerHUDEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

