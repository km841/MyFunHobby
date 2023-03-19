#include "pch.h"
#include "PlayerMoveScript.h"
#include "Timer.h"
#include "Input.h"
#include "Transform.h"
#include "Controller.h"
#include "Physical.h"


PlayerMoveScript::PlayerMoveScript()
	: m_fSpeed(10.f)
{

}

PlayerMoveScript::~PlayerMoveScript()
{

}

void PlayerMoveScript::LateUpdate()
{
	//PxRigidDynamic* pActor = GetPhysical()->GetActor()->is<PxRigidDynamic>();
	//PxVec3 vCurrVelocity = pActor->getLinearVelocity();
	Vec3 vPos = {};

	if (IS_PRESS(KEY_TYPE::UP))
	{
		//vCurrVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetUp() * m_fSpeed * DELTA_TIME);
		vPos = GetTransform()->GetUp() * m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::DOWN))
	{
		//vCurrVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetUp() * -m_fSpeed * DELTA_TIME);
		vPos = GetTransform()->GetUp() * -m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::LEFT))
	{
		//vCurrVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetRight() * -m_fSpeed * DELTA_TIME);
		vPos = GetTransform()->GetRight() * -m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		//vCurrVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetRight() * m_fSpeed * DELTA_TIME);
		vPos = GetTransform()->GetRight() * m_fSpeed * DELTA_TIME;
	}

	//pActor->setLinearVelocity(vCurrVelocity);
	PlayerFilterShaders filter = PlayerFilterShaders();
	
	PxFilterData filterData = {};
	filterData.word0 = 1 << 0;
	filterData.word1 = 1 << 1;

	GetController()->Move(Conv::Vec3ToPxVec3(vPos), &filter, filterData);
}
