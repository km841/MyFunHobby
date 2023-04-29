#pragma once
#include "SkulSkill.h"
class HighWarlockSwapSkill :
    public SkulSkill
{
public:
	HighWarlockSwapSkill(const SkillInfo& skillInfo);
	virtual ~HighWarlockSwapSkill() = default;

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	
};

