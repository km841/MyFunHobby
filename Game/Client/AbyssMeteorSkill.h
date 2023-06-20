#pragma once
#include "SkulSkill.h"

class AbyssMeteor;
class IncompletedAbyssMeteor;
class AbyssMeteorSkill :
    public SkulSkill
{
public:
	AbyssMeteorSkill(const SkillInfo& skillInfo);
	virtual ~AbyssMeteorSkill() = default;

public:
	shared_ptr<AbyssMeteor> CreateAbyssMeteor(const Vec3& vPos);
	shared_ptr<IncompletedAbyssMeteor> CreateIncompletedAbyssMeteor(const Vec3& vPos);

private:
	void CreateFullChargingMeteor(const Vec3& vPos);
	void CreateInsufficientMeteor(const Vec3& vPos);

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;
};

