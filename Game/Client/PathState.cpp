#include "pch.h"
#include "PathState.h"
#include "Input.h"

PathState::PathState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void PathState::Update()
{
}

void PathState::Enter()
{
	if (!CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
		return;
	}
	else
	{
		AddChangeStateEvent(PLAYER_STATE::IDLE);
		return;
	}

	if (IS_PRESS(KEY_TYPE::LEFT) || IS_PRESS(KEY_TYPE::RIGHT))
	{
		AddChangeStateEvent(PLAYER_STATE::WALK);
		return;
	}

	// Skill State ÀüÀÌ
	if (m_pPlayer.lock()->GetActiveSkul()->IsSkillActiveFlag())
	{
		AddChangeStateEvent(PLAYER_STATE::SKILL);
		return;
	}

	assert(nullptr);
}

void PathState::Exit()
{
}

void PathState::PlayAnimation()
{
}
