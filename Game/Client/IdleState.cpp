#include "pch.h"
#include "IdleState.h"
#include "Player.h"
#include "Animator.h"
#include "PlayerChangeStateEvent.h"
#include "EventManager.h"
#include "Input.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "Scenes.h"
#include "Engine.h"

IdleState::IdleState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void IdleState::Update()
{
	if (IS_PRESS(KEY_TYPE::LEFT) || IS_PRESS(KEY_TYPE::RIGHT))
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::WALK));

	if (!CheckGrounded())
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::JUMP_RISE));

	if (IS_DOWN(KEY_TYPE::X))
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::ATTACK_A));
}

void IdleState::Enter()
{
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_Idle");
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
	m_pPlayer.lock()->GetRigidBody()->RemoveGravity();
}

void IdleState::Exit()
{
}
