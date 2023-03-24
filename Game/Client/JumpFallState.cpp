#include "pch.h"
#include "JumpFallState.h"
#include "Player.h"
#include "Animator.h"
#include "Input.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"
#include "RigidBody.h"

JumpFallState::JumpFallState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void JumpFallState::Update()
{
	if (!m_pPlayer.lock()->GetRigidBody()->IsGravityApplied())
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
}

void JumpFallState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_JumpFall", true, 2);
}

void JumpFallState::Exit()
{
}
