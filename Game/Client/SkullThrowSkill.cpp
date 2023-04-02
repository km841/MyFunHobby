#include "pch.h"
#include "SkullThrowSkill.h"
#include "Clock.h"
#include "GameObject.h"
#include "LittleBone.h"

SkullThrowSkill::SkullThrowSkill()
	: SkulSkill(3.0f, 0.5f)
{
	CreateConditionFunction();
}

void SkullThrowSkill::Update()
{
	m_tDuration.Update(DELTA_TIME);
}

void SkullThrowSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		weak_ptr<LittleBone> pLittleBone = static_pointer_cast<LittleBone>(pGameObject.lock());
		return pLittleBone.lock()->HasHead();
	};
}

void SkullThrowSkill::Enter()
{
	// Throw Head!
	static_pointer_cast<LittleBone>(m_pSkul.lock())->LoseHead();
}

void SkullThrowSkill::Exit()
{
	
}
