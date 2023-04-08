#include "pch.h"
#include "LittleBoneSwapSkill.h"
#include "Clock.h"

LittleBoneSwapSkill::LittleBoneSwapSkill()
	: SkulSkill(0.f, 2.f)
{
}

void LittleBoneSwapSkill::Update()
{
	m_tDuration.Update(DELTA_TIME);
}

void LittleBoneSwapSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void LittleBoneSwapSkill::Enter()
{
}

void LittleBoneSwapSkill::Exit()
{
}
