#pragma once
#include "SkulSkill.h"
class DevilBerserkerSwapSkill :
    public SkulSkill
{
public:
	DevilBerserkerSwapSkill(const SkillInfo& skillInfo);
	virtual ~DevilBerserkerSwapSkill() = default;

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	Timer m_tUpTimer;
	bool m_bUpFinishedFlag;
};

