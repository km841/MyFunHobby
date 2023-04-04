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
	// Path State 전이
	if (m_pPlayer.lock()->GetActiveSkul()->GetActiveAnimation().lock()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::PATH);
		return;
	}
	
	// Jump Rise State 전이
	if (!CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
		return;
	}

	// Skill State 전이
	if (m_pPlayer.lock()->GetActiveSkul()->IsSkillActiveFlag())
	{
		AddChangeStateEvent(PLAYER_STATE::SKILL);
		return;
	}

	// Dash State 전이
	if (IS_PRESS(KEY_TYPE::Z))
	{
		AddChangeStateEvent(PLAYER_STATE::DASH);
		return;
	}
}

void AttackBState::Enter()
{
	PlayAnimation();
}

void AttackBState::Exit()
{
}

void AttackBState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::ATTACK_B, false);
}
