#include "pch.h"
#include "StateMachine.h"
#include "GameObject.h"
#include "PlayerState.h"
#include "IdleState.h"
#include "WalkState.h"
#include "JumpRiseState.h"
#include "JumpFallState.h"
#include "Player.h"

StateMachine::StateMachine()
{
}

void StateMachine::Awake()
{
	m_mStateMap[PLAYER_STATE::IDLE]		 = make_shared<IdleState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::WALK]      = make_shared<WalkState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::JUMP_RISE] = make_shared<JumpRiseState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::JUMP_FALL] = make_shared<JumpFallState>(m_pPlayer.lock());
	

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
