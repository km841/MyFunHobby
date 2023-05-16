#pragma once
#include "SkulSkill.h"

class AbyssOrb;
class AbyssOrbSkill :
    public SkulSkill
{
public:
	AbyssOrbSkill(const SkillInfo& skillInfo);
	virtual ~AbyssOrbSkill() = default;

	shared_ptr<AbyssOrb> CreateAbyssOrb();

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;
};

