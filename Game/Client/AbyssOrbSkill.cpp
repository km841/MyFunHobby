#include "pch.h"
#include "AbyssOrbSkill.h"
#include "AbyssOrb.h"

AbyssOrbSkill::AbyssOrbSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
	CreateConditionFunction();
	m_fMaxChargingTime = 5.f;
}

void AbyssOrbSkill::Update()
{
	SkulSkill::Update();
}

void AbyssOrbSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void AbyssOrbSkill::Enter()
{
	// Create Orb!

	int32 a = 0;
}

void AbyssOrbSkill::Exit()
{
}
