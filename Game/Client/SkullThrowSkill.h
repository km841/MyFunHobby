#pragma once
#include "SkulSkill.h"
class SkullThrowSkill :
    public SkulSkill
{
public:
	SkullThrowSkill(const SkillInfo& skillInfo);
	virtual ~SkullThrowSkill() = default;

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	float m_fThrowSpeed;
};

