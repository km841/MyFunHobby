#include "pch.h"
#include "StateMachine.h"
#include "GameObject.h"
#include "PlayerState.h"
#include "IdleState.h"
#include "WalkState.h"
#include "JumpRiseState.h"
#include "JumpFallState.h"
#include "JumpAttackState.h"
#include "AttackAState.h"
#include "AttackBState.h"
#include "DashState.h"
#include "Player.h"

StateMachine::StateMachine()
{
}

void StateMachine::Awake()
{
	m_mStateMap[PLAYER_STATE::IDLE]		   = make_shared<IdleState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::WALK]        = make_shared<WalkState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::JUMP_RISE]   = make_shared<JumpRiseState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::JUMP_FALL]   = make_shared<JumpFallState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::ATTACK_A]    = make_shared<AttackAState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::ATTACK_B]    = make_shared<AttackBState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::JUMP_ATTACK] = make_shared<JumpAttackState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::DASH]		   = make_shared<DashState>(m_pPlayer.lock());

	for (int32 i = 0; i < PLAYER_STATE_COUNT; ++i)
	{
		m_mStateMap[static_cast<PLAYER_STATE>(i)]->Awake();
	}
	
	ChangePlayerState(static_pointer_cast<Player>(m_pPlayer.lock())->GetPlayerStateEnum());
}

void StateMachine::Update()
{
	if (m_pActiveState)
		m_pActiveState->Update();
}

void StateMachine::ChangePlayerState(PLAYER_STATE ePlayerState)
{
	if (m_pActiveState)
		m_pActiveState->Exit();

	auto iter = m_mStateMap.find(ePlayerState);
	assert(iter != m_mStateMap.end());

	m_pActiveState = iter->second;
	m_pActiveState->Enter();

	m_pPlayer.lock()->SetPlayerStateEnum(ePlayerState);
}
