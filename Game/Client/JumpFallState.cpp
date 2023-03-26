#include "pch.h"
#include "JumpFallState.h"
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

JumpFallState::JumpFallState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void JumpFallState::Update()
{
	if (CheckGrounded())
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
}

void JumpFallState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_JumpFall", true, 2);
	m_pPlayer.lock()->GetRigidBody()->ApplyGravity();
}

void JumpFallState::Exit()
{
}
