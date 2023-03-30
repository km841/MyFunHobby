#include "pch.h"
#include "DashState.h"
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

DashState::DashState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void DashState::Update()
{
	if (!CheckGrounded())
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), PLAYER_STATE::JUMP_RISE));
		return;
	}
}

void DashState::Enter()
{
}

void DashState::Exit()
{
}
