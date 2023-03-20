#include "pch.h"
#include "PlayerMoveScript.h"
#include "Timer.h"
#include "Input.h"
#include "Transform.h"
#include "Controller.h"
#include "Physical.h"
#include "GameObject.h"
#include "Collider.h"


PlayerMoveScript::PlayerMoveScript()
	: m_fSpeed(10.f)
	, m_FilterShaders{}
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
		GetGameObject()->SetDirection(DIRECTION::LEFT);
	}

	else if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		//vCurrVelocity += Conv::Vec3ToPxVec3(GetTransform()->GetRight() * m_fSpeed * DELTA_TIME);
		vPos = GetTransform()->GetRight() * m_fSpeed * DELTA_TIME;
		GetGameObject()->SetDirection(DIRECTION::RIGHT);
	}

	//pActor->setLinearVelocity(vCurrVelocity);
	GetController()->Move(Conv::Vec3ToPxVec3(vPos), &m_FilterShaders, GetCollider()->GetFilterData());
}
