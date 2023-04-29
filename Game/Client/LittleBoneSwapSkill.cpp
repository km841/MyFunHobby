#include "pch.h"
#include "LittleBoneSwapSkill.h"
#include "Clock.h"
#include "Skul.h"
#include "RigidBody.h"
#include "Clock.h"
#include "Player.h"

LittleBoneSwapSkill::LittleBoneSwapSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
	, m_fSpeed(200.f)
{
}

void LittleBoneSwapSkill::Update()
{
	SkulSkill::Update();
	uint8 iDirection = static_cast<uint8>(m_pSkul.lock()->GetDirection());


	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(AXIS::X, iDirection ? -m_fSpeed : m_fSpeed);
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
