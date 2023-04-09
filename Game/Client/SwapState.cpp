#include "pch.h"
#include "SwapState.h"
#include "Player.h"
#include "SkulSkill.h"
#include "RigidBody.h"

SwapState::SwapState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void SwapState::Update()
{
	// Swap Skill
	weak_ptr<SkulSkill> pSwapSkill = m_pPlayer.lock()->GetActiveSkul()->GetSwapSkill();

	if (pSwapSkill.lock()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::PATH);
	}
	else
	{
		pSwapSkill.lock()->Update();
	}

	if (CheckGrounded())
	{
		// 임시 코드
		//m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
		m_pPlayer.lock()->GetRigidBody()->RemoveGravity();
	}
}

void SwapState::Enter()
{
	m_pPlayer.lock()->SwapSkul();
	PlayAnimation();
	m_pPlayer.lock()->DisableSwapActiveFlag();

	weak_ptr<SkulSkill> pSwapSkill = m_pPlayer.lock()->GetActiveSkul()->GetSwapSkill();
	pSwapSkill.lock()->Enter();
	pSwapSkill.lock()->Activate();
}

void SwapState::Exit()
{
	weak_ptr<SkulSkill> pSwapSkill = m_pPlayer.lock()->GetActiveSkul()->GetSwapSkill();

	pSwapSkill.lock()->Exit();
	pSwapSkill.lock()->DeActivate();
}

void SwapState::PlayAnimation()
{
	weak_ptr<SkulSkill> pSwapSkill = m_pPlayer.lock()->GetActiveSkul()->GetSwapSkill();
	const wstring& szName = pSwapSkill.lock()->GetAnimationName();
	if (pSwapSkill.lock() && !szName.empty())
	{
		m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(szName, true);
	}
}
