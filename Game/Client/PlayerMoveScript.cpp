#include "pch.h"
#include "PlayerMoveScript.h"
#include "Timer.h"
#include "Input.h"
#include "Transform.h"
#include "Controller.h"
#include "Physical.h"
#include "GameObject.h"
#include "Collider.h"
#include "Engine.h"
#include "RigidBody.h"


PlayerMoveScript::PlayerMoveScript()
	: m_fSpeed(10.f)
	, m_FilterShaders{}
	, m_fJumpSpeed(100.f)
{
}

PlayerMoveScript::~PlayerMoveScript()
{
}

void PlayerMoveScript::LateUpdate()
{
	Vec3 vVelocity = GetRigidBody()->GetVelocity();

	if (IS_PRESS(KEY_TYPE::UP))
	{
		vVelocity += GetTransform()->GetUp() * m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::DOWN))
	{
		vVelocity += GetTransform()->GetUp() * -m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::LEFT))
	{
		vVelocity += GetTransform()->GetRight() * -m_fSpeed * DELTA_TIME;
		GetGameObject()->SetDirection(DIRECTION::LEFT);
	}

	else if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		vVelocity += GetTransform()->GetRight() * m_fSpeed * DELTA_TIME;
		GetGameObject()->SetDirection(DIRECTION::RIGHT);
	}

	if (IS_PRESS(KEY_TYPE::C))
	{
		vVelocity += GetTransform()->GetUp() * m_fJumpSpeed * DELTA_TIME;
	}
	
	GetRigidBody()->SetVelocity(vVelocity);
}
