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
	PxRigidDynamic* pActor = GetPhysical()->GetActor()->is<PxRigidDynamic>();
	PxVec3 currVelocity = pActor->getLinearVelocity();

	if (IS_PRESS(KEY_TYPE::UP))
	{
		currVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetUp() * m_fSpeed * DELTA_TIME);
	}

	if (IS_PRESS(KEY_TYPE::DOWN))
	{
		currVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetUp() * -m_fSpeed * DELTA_TIME);
	}

	if (IS_PRESS(KEY_TYPE::LEFT))
	{
		currVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetRight() * -m_fSpeed * DELTA_TIME);
	}

	if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		currVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetRight() * m_fSpeed * DELTA_TIME);
	}

	pActor->setLinearVelocity(currVelocity);

	PlayerFilterShaders filter = PlayerFilterShaders();
	
	PxFilterData filterData = {};
	filterData.word0 = 1 << 0;
	filterData.word1 = 1 << 1;

	//GetController()->Move(Conv::Vec3ToPxVec3(vPos), &filter, filterData);
}
