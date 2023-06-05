#include "pch.h"
#include "PlayerMoveScript.h"
#include "Clock.h"
#include "Input.h"
#include "Transform.h"
#include "Physical.h"
#include "GameObject.h"
#include "Collider.h"
#include "Engine.h"
#include "RigidBody.h"
#include "InterfaceManager.h"
#include "DialogueUI.h"
#include "Player.h"
#include "Skul.h"
#include "SkulSkill.h"
#include "PlayerState.h"


PlayerMoveScript::PlayerMoveScript()
	: m_fSpeed(400.f)
	, m_fJumpSpeed(1300.f)
	, m_FilterShaders{}
	, m_tPauseTimer(3.f)
	, m_bPauseFlag(false)
{
}

PlayerMoveScript::~PlayerMoveScript()
{
}

void PlayerMoveScript::LateUpdate()
{
	Vec3 vVelocity = {};
	shared_ptr<Player> pPlayer = static_pointer_cast<Player>(GetGameObject());

	if (GET_SINGLE(Clock)->IsPause())
		return;

	if (pPlayer->IsPause())
	{
		if (!m_bPauseFlag)
		{
			m_bPauseFlag = true;
			m_tPauseTimer.Start();
		}

		m_tPauseTimer.Update(OBJECT_DELTA_TIME);
		if (m_tPauseTimer.IsFinished())
		{
			m_bPauseFlag = false;
			pPlayer->Play();
		}

		pPlayer->GetRigidBody()->SetVelocity(Vec3::Zero);
		return;
	}

	if (IS_PRESS(KEY_TYPE::LEFT))
	{
		vVelocity = VEC3_RIGHT_NORMAL * -pPlayer->GetStatus()->fSpeed;
		
		if (PLAYER_STATE::DASH != GetPlayerStateEnum() &&
			PLAYER_STATE::SWAP != GetPlayerStateEnum())
		{
			pPlayer->SetDirection(DIRECTION::LEFT);
			if (pPlayer->DoesTileExistInDirection(DIRECTION::LEFT, 0.1f))
				GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
		}
	}

	else if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		vVelocity = VEC3_RIGHT_NORMAL * pPlayer->GetStatus()->fSpeed;
	
		if (PLAYER_STATE::DASH != GetPlayerStateEnum() &&
			PLAYER_STATE::SWAP != GetPlayerStateEnum())
		{
			pPlayer->SetDirection(DIRECTION::RIGHT);
			if (pPlayer->DoesTileExistInDirection(DIRECTION::RIGHT, 0.1f))
				GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
		}
	}

	if (IS_DOWN(KEY_TYPE::C))
	{
		if (pPlayer->GetJumpCount() && 
			PLAYER_STATE::DASH != pPlayer->GetPlayerStateEnum() && 
			PLAYER_STATE::CHARGING != pPlayer->GetPlayerStateEnum() &&
			PLAYER_STATE::SWAP != pPlayer->GetPlayerStateEnum() &&
			PLAYER_STATE::SKILL != pPlayer->GetPlayerStateEnum())
		{
			vVelocity = VEC3_UP_NORMAL * m_fJumpSpeed;
			GetRigidBody()->SetVelocity(vVelocity);
			pPlayer->DecreaseJumpCount();
		}
	}

	if (IS_NONE(KEY_TYPE::LEFT) && IS_NONE(KEY_TYPE::RIGHT))
	{
		if (PLAYER_STATE::DASH != pPlayer->GetPlayerStateEnum() &&
			PLAYER_STATE::SWAP != pPlayer->GetPlayerStateEnum())
			GetRigidBody()->SetVelocity(AXIS::X, 0.f);
	}

	pPlayer->ReorganizePosition();
	pPlayer->ReorganizePosition();
}
