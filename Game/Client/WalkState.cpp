#include "pch.h"
#include "WalkState.h"
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

WalkState::WalkState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::WALK;
}

void WalkState::Update()
{
	// Idle State 전이
	if (IS_NONE(KEY_TYPE::LEFT) && IS_NONE(KEY_TYPE::RIGHT))
	{
		AddChangeStateEvent(PLAYER_STATE::IDLE);
		return;
	}

	// JumpRise State 전이
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

	// Swap State 전이
	if (m_pPlayer.lock()->IsSwapActiveFlag())
	{
		AddChangeStateEvent(PLAYER_STATE::SWAP);
		return;
	}

	// Attack A State 전이
	if (IS_PRESS(KEY_TYPE::X))
	{
		AddChangeStateEvent(PLAYER_STATE::ATTACK_A);
		return;
	}

	// Dash State 전이
	if (IS_PRESS(KEY_TYPE::Z))
	{
		AddChangeStateEvent(PLAYER_STATE::DASH);
		return;
	}
	
}

void WalkState::Enter()
{
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
	PlayAnimation();
}

void WalkState::Exit()
{
}

void WalkState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::WALK);
}
