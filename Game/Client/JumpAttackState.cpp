#include "pch.h"
#include "JumpAttackState.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"
#include "Engine.h"
#include "Animation.h"
#include "Animator.h"

JumpAttackState::JumpAttackState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void JumpAttackState::Update()
{
	if (m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->IsFinished())
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::JUMP_RISE));
		return;
	}

	if (CheckGrounded())
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
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
