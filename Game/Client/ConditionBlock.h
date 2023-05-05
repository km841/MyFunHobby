#pragma once
class ConditionBlock
{
public:
	ConditionBlock() = default;
	virtual ~ConditionBlock() = default;

public:
	virtual bool IsTrigger() = 0;
};

