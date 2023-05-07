#pragma once
#include "ConditionBlock.h"
class IfAlwaysTrue :
    public ConditionBlock
{
public:
	IfAlwaysTrue() = default;
	virtual ~IfAlwaysTrue() = default;

public:
	virtual bool IsTrigger() { return true; }
};

