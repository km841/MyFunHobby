#pragma once
#include "ConditionBlock.h"
class IfTakedMapReward :
    public ConditionBlock
{
public:
	IfTakedMapReward() = default;
	virtual ~IfTakedMapReward() = default;

public:
	virtual bool IsTrigger();
};

