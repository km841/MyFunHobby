#include "pch.h"
#include "HighWarlockChargingScript.h"
#include "HighWarlock.h"
#include "SkulSkill.h"
#include "GlobalEffect.h"
#include "Player.h"
#include "ComponentObject.h"
#include "SoundSource.h"
#include "Scenes.h"
#include "Scene.h"
#include "Resources.h"

HighWarlockChargingScript::HighWarlockChargingScript(shared_ptr<HighWarlock> pHighWarlock)
	: m_pHighWarlock(pHighWarlock)
	, m_eRealTimePlayerState(PLAYER_STATE::END)
	, m_bChargedFlag(false)
	, m_bCompleteFlag(false)
{
}

HighWarlockChargingScript::~HighWarlockChargingScript()
{
}

void HighWarlockChargingScript::LateUpdate()
{
	if (PLAYER_STATE::CHARGING == m_pHighWarlock.lock()->GetPlayer().lock()->GetPlayerStateEnum() &&
		PLAYER_STATE::CHARGING != m_eRealTimePlayerState)
	{
		m_pHighWarlock.lock()->EnableAndInitTrailEffect();
	}

	if (PLAYER_STATE::CHARGING == m_eRealTimePlayerState)
	{
		weak_ptr<SkulSkill> pSkulSkill = m_pHighWarlock.lock()->GetActiveSkill();
		float fProgress = pSkulSkill.lock()->LoadChargingProgress();
		
		if (fProgress > 0.75f && !m_bChargedFlag)
		{
			m_pHighWarlock.lock()->EnableAndInitChargedEffect();
			m_bChargedFlag = true;
		}

		if (fProgress > 0.99f && !m_bCompleteFlag)
		{
			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"HighWarlock_Charged_End", L"..\\Resources\\Sound\\HighWarlock_Charge_End.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();

			m_pHighWarlock.lock()->CreateCompletedSmokeAndAddedToScene();
			m_bCompleteFlag = true;
		}
	}

	if (PLAYER_STATE::SKILL == m_eRealTimePlayerState)
	{
		m_pHighWarlock.lock()->DisableTrailEffect();
		m_bChargedFlag = false;
		m_bCompleteFlag = false;
	}

	m_eRealTimePlayerState = m_pHighWarlock.lock()->GetPlayer().lock()->GetPlayerStateEnum();
}
