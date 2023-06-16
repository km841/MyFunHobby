#include "pch.h"
#include "PauseIdleState.h"
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

PauseIdleState::PauseIdleState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void PauseIdleState::Update()
{

}

void PauseIdleState::Enter()
{
	PlayAnimation();
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
	m_pPlayer.lock()->GetRigidBody()->RemoveGravity();
	m_pPlayer.lock()->RefreshJumpCount();
}

void PauseIdleState::Exit()
{
}

void PauseIdleState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::IDLE);
}
