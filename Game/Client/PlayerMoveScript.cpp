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
#include "UIManager.h"
#include "DialogueUI.h"


PlayerMoveScript::PlayerMoveScript()
	: m_fSpeed(400.f)
	, m_fJumpSpeed(1300.f)
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
		vVelocity = VEC3_RIGHT_NORMAL * -m_fSpeed;
		GetGameObject()->SetDirection(DIRECTION::LEFT);

		if (PLAYER_STATE::DASH != GetPlayerStateEnum())
			GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
	}

	else if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		vVelocity = VEC3_RIGHT_NORMAL * m_fSpeed;
		GetGameObject()->SetDirection(DIRECTION::RIGHT);

		if (PLAYER_STATE::DASH != GetPlayerStateEnum())
			GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
	}

	if (IS_DOWN(KEY_TYPE::C))
	{

		vVelocity = VEC3_UP_NORMAL * m_fJumpSpeed;
		GetRigidBody()->SetVelocity(vVelocity);

		// Test Code
		//GetGameObject()->GetStatus()->TakeDamage(1);

		//GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->GetTransform()->SetLocalPosition(Vec3(800.f, 450.f, 80.f));
		//if (GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->IsEnable())
		//	GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->Disable();
		
		//else
		//	GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->Enable();
	}
}
