#include "pch.h"
#include "JumpFallState.h"
#include "Player.h"
#include "Animator.h"
#include "Input.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "Scenes.h"
#include "Engine.h"

JumpFallState::JumpFallState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::JUMP_FALL;
}

void JumpFallState::Update()
{
	const Vec3& vVelocity = m_pPlayer.lock()->GetRigidBody()->GetVelocity();
	if (vVelocity.y > 0.f)
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
		return;
	}

	if (IS_PRESS(KEY_TYPE::X))
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_ATTACK);
		return;
	}

	if (CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::IDLE);
		return;
	}

	if (IS_PRESS(KEY_TYPE::Z))
	{
		AddChangeStateEvent(PLAYER_STATE::DASH);
		return;
	}
}

void JumpFallState::Enter()
{
	PlayAnimation();
}

void JumpFallState::Exit()
{
}

void JumpFallState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::JUMP_FALL, true, 2);
}
