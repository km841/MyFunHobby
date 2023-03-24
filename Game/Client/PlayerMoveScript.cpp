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
	, m_fJumpSpeed(20.f)
	, m_FilterShaders{}
{
}

PlayerMoveScript::~PlayerMoveScript()
{
}

void PlayerMoveScript::LateUpdate()
{
	Vec3 vVelocity = {};


	if (IS_PRESS(KEY_TYPE::LEFT))
	{
		vVelocity = GetTransform()->GetRight() * -m_fSpeed;
		GetGameObject()->SetDirection(DIRECTION::LEFT);
		GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
	}

	else if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		vVelocity = GetTransform()->GetRight() * m_fSpeed;
		GetGameObject()->SetDirection(DIRECTION::RIGHT);
		GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
	}

	if (IS_DOWN(KEY_TYPE::C))
	{
		if (PLAYER_STATE::JUMP_RISE != GetTransform()->GetPlayerStateEnum() &&
			PLAYER_STATE::JUMP_FALL != GetTransform()->GetPlayerStateEnum())
		{
			vVelocity = GetTransform()->GetUp() * m_fJumpSpeed;
			GetRigidBody()->AddVelocity(vVelocity);
		}
	}
}
