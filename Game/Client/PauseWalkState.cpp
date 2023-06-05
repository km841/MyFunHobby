#include "pch.h"
#include "PauseWalkState.h"
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

PauseWalkState::PauseWalkState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::PAUSE_WALK;
}

void PauseWalkState::Update()
{
}

void PauseWalkState::Enter()
{
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
	PlayAnimation();
}

void PauseWalkState::Exit()
{
}

void PauseWalkState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::WALK);
}
