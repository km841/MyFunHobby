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
	m_ePlayerState = PLAYER_STATE::ATTACK_A;
}

void AttackAState::Update()
{
	if (m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::IDLE);
		return;
	}
	
	float fRatio = m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->GetAnimationProgress();
	if (fRatio >= 0.75f && IS_PRESS(KEY_TYPE::X))
	{
		AddChangeStateEvent(PLAYER_STATE::ATTACK_B);
		return;
	}
	
	if (!CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
		return;
	}

	if (IS_PRESS(KEY_TYPE::Z))
	{
		AddChangeStateEvent(PLAYER_STATE::DASH);
		return;
	}
}

void AttackAState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_AttackA", false);
}

void AttackAState::Exit()
{

}
