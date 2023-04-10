#include "pch.h"
#include "HighWarlockSwapSkill.h"
#include "Clock.h"
#include "Skul.h"
#include "HighWarlock.h"
#include "GlobalEffect.h"

HighWarlockSwapSkill::HighWarlockSwapSkill()
	: SkulSkill(SKILL_TYPE::INSTANT, 0.f, 0.f)
{
}

void HighWarlockSwapSkill::Update()
{
	SkulSkill::Update();
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
	weak_ptr<HighWarlock> pHighWarlock = static_pointer_cast<HighWarlock>(m_pSkul.lock());
	pHighWarlock.lock()->ActiveAbyssField();
}

void HighWarlockSwapSkill::Exit()
{
	//weak_ptr<HighWarlock> pHighWarlock = static_pointer_cast<HighWarlock>(m_pSkul.lock());
	//pHighWarlock.lock()->DeActiveAbyssField();
}
