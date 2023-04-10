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


	assert(nullptr);
}

void PathState::Exit()
{
}

void PathState::PlayAnimation()
{
}
