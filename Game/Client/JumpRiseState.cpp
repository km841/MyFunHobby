#include "pch.h"
#include "JumpRiseState.h"
#include "Player.h"
#include "Animator.h"
#include "Input.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "Scenes.h"
#include "Engine.h"

JumpRiseState::JumpRiseState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void JumpRiseState::Update()
{
	const Vec3& vVelocity = m_pPlayer.lock()->GetRigidBody()->GetVelocity();
	if (vVelocity.y < 0.f)
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::JUMP_FALL));

	if (CheckGrounded())
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
	
}

void JumpRiseState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_JumpRise");
	m_pPlayer.lock()->GetRigidBody()->ApplyGravity();
}

void JumpRiseState::Exit()
{
}
