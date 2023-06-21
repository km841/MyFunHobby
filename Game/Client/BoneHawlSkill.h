#pragma once
#include "SkulSkill.h"
class BoneHawlSkill :
    public SkulSkill
{
public:
	BoneHawlSkill(const SkillInfo& skillInfo);
	virtual ~BoneHawlSkill() = default;

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;
};

