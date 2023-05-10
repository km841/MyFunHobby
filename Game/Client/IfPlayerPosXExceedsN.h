#pragma once
#include "ConditionBlock.h"
class IfPlayerPosXExceedsN :
    public ConditionBlock
{
public:
	IfPlayerPosXExceedsN(float fPlayerX);
	virtual ~IfPlayerPosXExceedsN() = default;

public:
	virtual bool IsTrigger();

private:
	float m_fPlayerX;
};

