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
}

void JumpAttackState::Update()
{
	if (m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
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

void JumpAttackState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_JumpAttack", false);
}

void JumpAttackState::Exit()
{
}
