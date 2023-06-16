#include "pch.h"
#include "PauseJumpFallState.h"
#include "Player.h"
#include "RigidBody.h"
#include "Skul.h"

PauseJumpFallState::PauseJumpFallState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::PAUSE_JUMP_FALL;
}

void PauseJumpFallState::Update()
{
	if (CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::PAUSE_IDLE);
		return;
	}
}

void PauseJumpFallState::Enter()
{
	PlayAnimation();
}

void PauseJumpFallState::Exit()
{
}

void PauseJumpFallState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::JUMP_FALL, true, 2);
}
