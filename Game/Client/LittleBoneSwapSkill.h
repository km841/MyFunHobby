#pragma once
#include "SkulSkill.h"
class LittleBoneSwapSkill :
    public SkulSkill
{
public:
	LittleBoneSwapSkill(const SkillInfo& skillInfo);
	virtual ~LittleBoneSwapSkill() = default;

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	float m_fSpeed;
};

