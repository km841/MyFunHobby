#pragma once
#include "DungeonEvent.h"
class PlayDungeonEvent :
    public DungeonEvent
{
public:
	PlayDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~PlayDungeonEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

