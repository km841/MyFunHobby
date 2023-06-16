#pragma once
#include "DungeonEvent.h"
class EnableCameraTrackingEvent :
    public DungeonEvent
{
public:
	EnableCameraTrackingEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~EnableCameraTrackingEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

