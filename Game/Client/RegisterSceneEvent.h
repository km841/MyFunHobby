#pragma once
#include "DungeonEvent.h"
class RegisterSceneEvent :
    public DungeonEvent
{
public:
	RegisterSceneEvent(shared_ptr<ConditionBlock> pConditionBlock, EVENT_TYPE eEventType, float fDuration);
	virtual ~RegisterSceneEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	EVENT_TYPE m_eEventType;
	float m_fDuration;
};

