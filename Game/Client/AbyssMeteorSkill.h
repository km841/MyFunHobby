#pragma once
#include "SkulSkill.h"

class AbyssMeteor;
class AbyssMeteorSkill :
    public SkulSkill
{
public:
	AbyssMeteorSkill(const SkillInfo& skillInfo);
	virtual ~AbyssMeteorSkill() = default;

public:
	shared_ptr<AbyssMeteor> CreateAbyssMeteor();

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;
};

