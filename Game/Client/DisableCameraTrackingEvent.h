#pragma once
#include "DungeonEvent.h"
class DisableCameraTrackingEvent :
    public DungeonEvent
{
public:
	DisableCameraTrackingEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~DisableCameraTrackingEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

