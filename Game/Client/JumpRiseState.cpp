#include "pch.h"
#include "JumpRiseState.h"
#include "Player.h"
#include "Animator.h"
#include "Input.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"
#include "RigidBody.h"

JumpRiseState::JumpRiseState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void JumpRiseState::Update()
{
	if (!m_pPlayer.lock()->GetRigidBody()->IsGravityApplied())
	{
		if (IS_DOWN(KEY_TYPE::LEFT) || IS_DOWN(KEY_TYPE::RIGHT))
			GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::WALK));
		
		if (IS_NONE(KEY_TYPE::LEFT) && IS_NONE(KEY_TYPE::RIGHT))
			GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
	}

	const Vec3& vVelocity = m_pPlayer.lock()->GetRigidBody()->GetVelocity();
	if (vVelocity.y < 0.f)
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::JUMP_FALL));
	
}

void JumpRiseState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_JumpRise");
}

void JumpRiseState::Exit()
{
}
