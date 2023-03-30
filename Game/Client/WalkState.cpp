#include "pch.h"
#include "WalkState.h"
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

WalkState::WalkState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{

}

void WalkState::Update()
{
	if (IS_NONE(KEY_TYPE::LEFT) && IS_NONE(KEY_TYPE::RIGHT))
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::IDLE));
		return;
	}

	if (!CheckGrounded())
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::JUMP_RISE));
		return;
	}

	if (IS_PRESS(KEY_TYPE::X))
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::ATTACK_A));
		return;
	}
	
}

void WalkState::Enter()
{
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_Walk");
}

void WalkState::Exit()
{
}
