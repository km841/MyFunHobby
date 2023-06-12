#pragma once
#include "DungeonEvent.h"
class CameraUnfixEvent :
    public DungeonEvent
{
public:
	CameraUnfixEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~CameraUnfixEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

