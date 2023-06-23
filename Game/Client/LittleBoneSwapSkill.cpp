#include "pch.h"
#include "LittleBoneSwapSkill.h"
#include "Clock.h"
#include "Skul.h"
#include "RigidBody.h"
#include "Clock.h"
#include "Player.h"
#include "Transform.h"
#include "CollisionManager.h"

LittleBoneSwapSkill::LittleBoneSwapSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
	, m_fSpeed(200.f)
	, m_tDamageTick(0.2f)
{
}

void LittleBoneSwapSkill::Update()
{
	SkulSkill::Update();
	uint8 iDirection = static_cast<uint8>(m_pSkul.lock()->GetDirection());

	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(AXIS::X, iDirection ? -m_fSpeed : m_fSpeed);

	if (!m_tDamageTick.IsRunning())
		m_tDamageTick.Start();

	m_tDamageTick.Update(OBJECT_DELTA_TIME);

	const Vec3& vSize = m_pSkul.lock()->GetTransform()->GetLocalScale();
	Vec3 vMyPos = m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPhysicalPosition();
	
	if (m_tDamageTick.IsFinished())
	{
		GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(
			vMyPos,
			vSize * 2.f,
			Vec3(0.f, 0.f, 0.f),
			static_cast<float>(RANDOM(3, 10)), DAMAGE_TYPE::FROM_PLAYER_MELEE, L"..\\Resources\\Sound\\Hit_Blunt_Large.wav");

		m_tDamageTick.Reset();
	}
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
