#include "pch.h"
#include "DevilBerserkerSwapSkill.h"

DevilBerserkerSwapSkill::DevilBerserkerSwapSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
}

void DevilBerserkerSwapSkill::Update()
{
	SkulSkill::Update();
}

void DevilBerserkerSwapSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void DevilBerserkerSwapSkill::Enter()
{
}

void DevilBerserkerSwapSkill::Exit()
{
}
