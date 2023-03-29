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
}

void AttackBState::Update()
{
	if (m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->IsFinished())
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
	
	if (!CheckGrounded())
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::JUMP_RISE));
}

void AttackBState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_AttackB", false);
}

void AttackBState::Exit()
{
}
