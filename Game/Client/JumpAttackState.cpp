#include "pch.h"
#include "JumpAttackState.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"
#include "Engine.h"
#include "Animation.h"
#include "Animator.h"
#include "Input.h"

JumpAttackState::JumpAttackState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::JUMP_ATTACK;
}

void JumpAttackState::Update()
{
	// Path State 전이
	if (m_pPlayer.lock()->GetActiveSkul()->GetActiveAnimation().lock()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::PATH);
		return;
	}

	// Idle State 전이
	if (CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::IDLE);
		return;
	}

	// Skill State 전이
	if (m_pPlayer.lock()->GetActiveSkul()->IsSkillActiveFlag())
	{
		AddChangeStateEvent(PLAYER_STATE::SKILL);
		return;
	}

	// Swap State 전이
	if (m_pPlayer.lock()->IsSwapActiveFlag())
	{
		AddChangeStateEvent(PLAYER_STATE::SWAP);
		return;
	}

	// Dash State 전이
	if (IS_PRESS(KEY_TYPE::Z))
	{
		AddChangeStateEvent(PLAYER_STATE::DASH);
		return;
	}
}

void JumpAttackState::Enter()
{
	PlayAnimation();
}

void JumpAttackState::Exit()
{
}

void JumpAttackState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::JUMP_ATTACK, false);
}
