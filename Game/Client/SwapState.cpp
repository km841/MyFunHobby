#include "pch.h"
#include "SwapState.h"
#include "Player.h"
#include "SkulSkill.h"

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
}

void SwapState::Enter()
{
	PlayAnimation();
	m_pPlayer.lock()->SwapSkul();
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
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(szName, true);
}
