#pragma once
#include "SkulSkill.h"
class MadRushSkill :
    public SkulSkill
{
public:
	MadRushSkill(const SkillInfo& skillInfo);
	virtual ~MadRushSkill() = default;

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	void CreateSlashEffectAndAddedToScene();


};

