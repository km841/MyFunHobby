#include "pch.h"
#include "StateMachine.h"
#include "GameObject.h"
#include "PlayerState.h"
#include "IdleState.h"
#include "PauseIdleState.h"
#include "WalkState.h"
#include "PauseWalkState.h"
#include "JumpRiseState.h"
#include "JumpFallState.h"
#include "PauseJumpFallState.h"
#include "JumpAttackState.h"
#include "AttackState.h"
#include "DashState.h"
#include "SkillState.h"
#include "PathState.h"
#include "SwapState.h"
#include "Player.h"
#include "ChargingState.h"

StateMachine::StateMachine()
{
}

void StateMachine::Awake()
{
	m_mStateMap[PLAYER_STATE::IDLE]				 = make_shared<IdleState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::PAUSE_IDLE]		 = make_shared<PauseIdleState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::WALK]				 = make_shared<WalkState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::PAUSE_WALK]		 = make_shared<PauseWalkState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::JUMP_RISE]		 = make_shared<JumpRiseState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::JUMP_FALL]		 = make_shared<JumpFallState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::PAUSE_JUMP_FALL]   = make_shared<PauseJumpFallState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::ATTACK]			 = make_shared<AttackState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::JUMP_ATTACK]		 = make_shared<JumpAttackState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::DASH]				 = make_shared<DashState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::SKILL]			 = make_shared<SkillState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::PATH]				 = make_shared<PathState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::SWAP]				 = make_shared<SwapState>(m_pPlayer.lock());
	m_mStateMap[PLAYER_STATE::CHARGING]			 = make_shared<ChargingState>(m_pPlayer.lock());

	for (int32 i = 0; i < PLAYER_STATE_COUNT; ++i)
	{
		if (m_mStateMap[static_cast<PLAYER_STATE>(i)])
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
