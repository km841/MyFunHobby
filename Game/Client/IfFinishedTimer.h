#pragma once
#include "ConditionBlock.h"
class IfFinishedTimer :
    public ConditionBlock
{
public:
	IfFinishedTimer(float fDuration);
	virtual ~IfFinishedTimer() = default;

public:
	virtual bool IsTrigger();

private:
	Timer m_tDuration;
};

