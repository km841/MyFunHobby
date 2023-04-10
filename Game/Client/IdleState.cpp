#include "pch.h"
#include "IdleState.h"
#include "Player.h"
#include "Animator.h"
#include "PlayerChangeStateEvent.h"
#include "EventManager.h"
#include "Input.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "Scenes.h"
#include "Engine.h"

IdleState::IdleState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::IDLE;
}

void IdleState::Update()
{
	// Walk State 전이
	if (IS_PRESS(KEY_TYPE::LEFT) || IS_PRESS(KEY_TYPE::RIGHT))
	{
		AddChangeStateEvent(PLAYER_STATE::WALK);
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
		SKILL_TYPE eSkillType = m_pPlayer.lock()->GetActiveSkul()->GetSkillActiveType();
		switch (eSkillType)
		{
		case SKILL_TYPE::INSTANT:
			AddChangeStateEvent(PLAYER_STATE::SKILL);
			break;
		case SKILL_TYPE::CHARGING:
			AddChangeStateEvent(PLAYER_STATE::CHARGING);
			break;
		}
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

void IdleState::Enter()
{
	PlayAnimation();
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
	m_pPlayer.lock()->GetRigidBody()->RemoveGravity();

	m_pPlayer.lock()->RefreshJumpCount();
}

void IdleState::Exit()
{
}

void IdleState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::IDLE);
}
