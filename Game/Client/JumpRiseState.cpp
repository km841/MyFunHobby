#include "pch.h"
#include "JumpRiseState.h"
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

JumpRiseState::JumpRiseState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::JUMP_RISE;
}

void JumpRiseState::Update()
{
	const Vec3& vVelocity = m_pPlayer.lock()->GetRigidBody()->GetVelocity();
	if (vVelocity.y < 0.f)
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_FALL);
		return;
	}

	if (IS_PRESS(KEY_TYPE::X))
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_ATTACK);
		return;
	}

	if (m_pPlayer.lock()->GetActiveSkul()->IsSkillActiveFlag())
	{
		AddChangeStateEvent(PLAYER_STATE::SKILL);
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

void JumpRiseState::Enter()
{
	PlayAnimation();
	m_pPlayer.lock()->GetRigidBody()->ApplyGravity();
}

void JumpRiseState::Exit()
{
}

void JumpRiseState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::JUMP_RISE);
}
