#include "pch.h"
#include "WalkState.h"
#include "Player.h"
#include "Animator.h"
#include "PlayerChangeStateEvent.h"
#include "EventManager.h"
#include "Input.h"

WalkState::WalkState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{

}

void WalkState::Update()
{
	if (IS_NONE(KEY_TYPE::LEFT) && IS_NONE(KEY_TYPE::RIGHT))
	{
		if (m_pPlayer.lock()->GetPlayerStateEnum() == PLAYER_STATE::WALK)
			GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
	}
}

void WalkState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_Walk");
}

void WalkState::Exit()
{
}
