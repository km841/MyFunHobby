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
#include "LittleBoneHead.h"

SkullThrowSkill::SkullThrowSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
	, m_fThrowSpeed(1000.f)
	, m_bContinue(false)
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
	m_bContinue = true;
	weak_ptr<LittleBone> pLittleBone = static_pointer_cast<LittleBone>(m_pSkul.lock());
	weak_ptr<LittleBoneHead> pHead = pLittleBone.lock()->GetHeadProjectile();
	pLittleBone.lock()->LoseHead();

	const Vec3& vLittleBonePos = pLittleBone.lock()->GetTransform()->GetLocalPosition();
	PxTransform pxTransform = pLittleBone.lock()->GetPlayer().lock()->GetPhysical()->GetActor<PxRigidDynamic>()->getGlobalPose();

	pHead.lock()->Enable();
	pHead.lock()->Initialize();
	pHead.lock()->GetPhysical()->GetActor<PxRigidDynamic>()->setGlobalPose(pxTransform);

	uint8 iDirection = static_cast<uint8>(pLittleBone.lock()->GetPlayer().lock()->GetDirection());
	pHead.lock()->SetDirection(pLittleBone.lock()->GetPlayer().lock()->GetDirection());
	pHead.lock()->GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 10.f));
	pHead.lock()->GetRigidBody()->RemoveGravityForDynamic();
}

void SkullThrowSkill::Exit()
{
}
