#include "pch.h"
#include "HighWarlockSwapSkill.h"
#include "Clock.h"

HighWarlockSwapSkill::HighWarlockSwapSkill()
	: SkulSkill(0.f, 0.f)
{
}

void HighWarlockSwapSkill::Update()
{
	m_tDuration.Update(DELTA_TIME);
}

void HighWarlockSwapSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void HighWarlockSwapSkill::Enter()
{
}

void HighWarlockSwapSkill::Exit()
{
}
