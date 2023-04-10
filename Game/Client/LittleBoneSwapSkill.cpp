#include "pch.h"
#include "LittleBoneSwapSkill.h"
#include "Clock.h"
#include "Skul.h"
#include "RigidBody.h"
#include "Clock.h"
#include "Player.h"

LittleBoneSwapSkill::LittleBoneSwapSkill()
	: SkulSkill(SKILL_TYPE::INSTANT, 0.f, 2.f)
	, m_fSpeed(300.f)
{
}

void LittleBoneSwapSkill::Update()
{
	SkulSkill::Update();
	uint8 iDirection = static_cast<uint8>(m_pSkul.lock()->GetDirection());
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(VEC3_RIGHT_NORMAL * (iDirection ? -m_fSpeed : m_fSpeed));
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
