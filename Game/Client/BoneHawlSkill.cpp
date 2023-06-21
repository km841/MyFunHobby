#include "pch.h"
#include "BoneHawlSkill.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Skul.h"
#include "DevilBerserker.h"

BoneHawlSkill::BoneHawlSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
	CreateConditionFunction();
}

void BoneHawlSkill::Update()
{
	SkulSkill::Update();
}

void BoneHawlSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void BoneHawlSkill::Enter()
{
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->RemoveGravity();
	m_pSkul.lock()->GetPlayer().lock()->Pause();
}

void BoneHawlSkill::Exit()
{
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->ApplyGravity();
	m_pSkul.lock()->GetPlayer().lock()->Play();
	static_pointer_cast<DevilBerserker>(m_pSkul.lock())->Demonization();

	// CameraShake
	// Damage
	// Impulse
	// CreateEffect
}
