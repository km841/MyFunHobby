#include "pch.h"
#include "AttackBState.h"
#include "Player.h"
#include "Animator.h"
#include "PlayerChangeStateEvent.h"
#include "EventManager.h"
#include "Input.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Transform.h"
#include "Physical.h"
#include "Engine.h"
#include "Scenes.h"
#include "Animation.h"

AttackBState::AttackBState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::ATTACK_B;
}

void AttackBState::Update()
{
	if (m_pPlayer.lock()->GetActiveSkul()->GetActiveAnimation()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::IDLE);
		return;
	}
	
	if (!CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
		return;
	}

	if (IS_PRESS(KEY_TYPE::Z))
	{
		AddChangeStateEvent(PLAYER_STATE::DASH);
		return;
	}
}

void AttackBState::Enter()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(m_ePlayerState, false);
}

void AttackBState::Exit()
{
}
