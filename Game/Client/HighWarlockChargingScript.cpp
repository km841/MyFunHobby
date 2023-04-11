#include "pch.h"
#include "HighWarlockChargingScript.h"
#include "HighWarlock.h"
#include "SkulSkill.h"
#include "GlobalEffect.h"
#include "Player.h"

HighWarlockChargingScript::HighWarlockChargingScript(shared_ptr<HighWarlock> pHighWarlock)
	: m_pHighWarlock(pHighWarlock)
	, m_ePlayerState(PLAYER_STATE::END)
	, m_bChargedFlag(false)
{
}

HighWarlockChargingScript::~HighWarlockChargingScript()
{
}

void HighWarlockChargingScript::LateUpdate()
{
	if (PLAYER_STATE::CHARGING == m_pHighWarlock.lock()->GetPlayer().lock()->GetPlayerStateEnum() &&
		PLAYER_STATE::CHARGING != m_ePlayerState)
	{
		m_pHighWarlock.lock()->EnableAndInitTrailEffect();
	}

	if (PLAYER_STATE::CHARGING == m_ePlayerState)
	{
		weak_ptr<SkulSkill> pSkulSkill = m_pHighWarlock.lock()->GetActiveSkill();
		float fProgress = pSkulSkill.lock()->LoadChargingProgress();
		
		if (fProgress > 0.75f && !m_bChargedFlag)
		{
			m_pHighWarlock.lock()->EnableAndInitChargedEffect();
			m_bChargedFlag = true;
		}
	}

	if (PLAYER_STATE::SKILL == m_ePlayerState)
	{
		m_pHighWarlock.lock()->DisableTrailEffect();
	}

	m_ePlayerState = m_pHighWarlock.lock()->GetPlayer().lock()->GetPlayerStateEnum();
}
