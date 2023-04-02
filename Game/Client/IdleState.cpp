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
	if (IS_PRESS(KEY_TYPE::LEFT) || IS_PRESS(KEY_TYPE::RIGHT))
	{
		AddChangeStateEvent(PLAYER_STATE::WALK);
		return;
	}

	if (!CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
		return;
	}

	if (m_pPlayer.lock()->GetActiveSkul()->IsSkillActiveFlag())
	{
		AddChangeStateEvent(PLAYER_STATE::SKILL);
		return;
	}

	if (IS_PRESS(KEY_TYPE::X))
	{
		AddChangeStateEvent(PLAYER_STATE::ATTACK_A);
		return;
	}

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
}

void IdleState::Exit()
{
}

void IdleState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::IDLE);
}
