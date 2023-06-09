#include "pch.h"
#include "SkillState.h"
#include "SkulSkill.h"
#include "Animation.h"
#include "RigidBody.h"

SkillState::SkillState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::SKILL;
}

void SkillState::Update()
{
	// Path State ����
	weak_ptr<SkulSkill> pActiveSkill = m_pPlayer.lock()->GetActiveSkul()->GetActiveSkill().lock();
	if (pActiveSkill.lock()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::PATH);
	}
	else
	{
		pActiveSkill.lock()->Update();
	}
}

void SkillState::Enter()
{
	PlayAnimation();
	weak_ptr<SkulSkill> pActiveSkill = m_pPlayer.lock()->GetActiveSkul()->GetActiveSkill().lock();

	pActiveSkill.lock()->Enter();
	pActiveSkill.lock()->Activate();
}

void SkillState::Exit()
{
	weak_ptr<SkulSkill> pActiveSkill = m_pPlayer.lock()->GetActiveSkul()->GetActiveSkill().lock();
	m_pPlayer.lock()->GetActiveSkul()->DisableSkillActiveFlag();

	pActiveSkill.lock()->Exit();
	pActiveSkill.lock()->DeActivate();
}

void SkillState::PlayAnimation()
{
	weak_ptr<SkulSkill> pActiveSkill = m_pPlayer.lock()->GetActiveSkul()->GetActiveSkill().lock();
	const wstring& szName = pActiveSkill.lock()->GetAnimationName();

	if (pActiveSkill.lock() && !szName.empty())
	{
		m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(szName, true, END_POINT);
	}
}
