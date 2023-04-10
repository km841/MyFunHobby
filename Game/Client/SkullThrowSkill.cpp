#include "pch.h"
#include "SkullThrowSkill.h"
#include "Clock.h"
#include "GameObject.h"
#include "LittleBone.h"
#include "PlayerProjectile.h"
#include "Physical.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"

SkullThrowSkill::SkullThrowSkill()
	: SkulSkill(SKILL_TYPE::INSTANT, 6.0f, 0.25f)
	, m_fThrowSpeed(500.f)
{
	CreateConditionFunction();
}

void SkullThrowSkill::Update()
{
	SkulSkill::Update();
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
	weak_ptr<LittleBone> pLittleBone = static_pointer_cast<LittleBone>(m_pSkul.lock());
	weak_ptr<PlayerProjectile> pProjectile = pLittleBone.lock()->GetHeadProjectile();
	pLittleBone.lock()->LoseHead();

	const Vec3& vLittleBonePos = pLittleBone.lock()->GetTransform()->GetLocalPosition();
	PxTransform pxTransform = pLittleBone.lock()->GetPlayer().lock()->GetPhysical()->GetActor<PxRigidDynamic>()->getGlobalPose();

	pProjectile.lock()->Enable();
	pProjectile.lock()->GetPhysical()->GetActor<PxRigidDynamic>()->setGlobalPose(pxTransform);

	uint8 iDirection = static_cast<uint8>(pLittleBone.lock()->GetPlayer().lock()->GetDirection());
	pProjectile.lock()->GetRigidBody()->SetVelocity(Vec3(iDirection ? -m_fThrowSpeed : m_fThrowSpeed, 0.f, 0.f));
}

void SkullThrowSkill::Exit()
{
}
