#include "pch.h"
#include "IdleState.h"
#include "Player.h"
#include "Animator.h"
#include "PlayerChangeStateEvent.h"
#include "EventManager.h"
#include "Input.h"

IdleState::IdleState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void IdleState::Update()
{
	if (IS_PRESS(KEY_TYPE::LEFT))
	{
		if (m_pPlayer.lock()->GetPlayerStateEnum() == PLAYER_STATE::IDLE)
			GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::WALK));
		m_pPlayer.lock()->SetDirection(DIRECTION::LEFT);
	}

	else if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		if (m_pPlayer.lock()->GetPlayerStateEnum() == PLAYER_STATE::IDLE)
			GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::WALK));
		m_pPlayer.lock()->SetDirection(DIRECTION::RIGHT);
	}
}

void IdleState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_Idle");
}

void IdleState::Exit()
{
}
