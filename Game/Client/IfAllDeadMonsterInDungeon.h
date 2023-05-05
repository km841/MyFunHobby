#pragma once
#include "ConditionBlock.h"
class IfAllDeadMonsterInDungeon :
    public ConditionBlock
{
public:
	IfAllDeadMonsterInDungeon() = default;
	virtual ~IfAllDeadMonsterInDungeon() = default;

public:
	virtual bool IsTrigger();
};

