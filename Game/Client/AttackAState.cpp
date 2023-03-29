#include "pch.h"
#include "AttackAState.h"
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

AttackAState::AttackAState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void AttackAState::Update()
{
	if (m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->IsFinished())
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
	
	float fRatio = m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->GetAnimationProgress();
	if (fRatio >= 0.6f && IS_DOWN(KEY_TYPE::X))
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::ATTACK_B));
	
	if (!CheckGrounded())
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::JUMP_RISE));
}

void AttackAState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_AttackA", false);
}

void AttackAState::Exit()
{

}
