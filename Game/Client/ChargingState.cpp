#include "pch.h"
#include "ChargingState.h"
#include "Clock.h"
#include "Input.h"
#include "SkulSkill.h"

ChargingState::ChargingState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
	, tChargingDuration(0.f)
{
}

void ChargingState::Update()
{
	weak_ptr<SkulSkill> pActiveSkill = m_pPlayer.lock()->GetActiveSkul()->GetActiveSkill().lock();
	SKILL_INDEX eSkillIndex = pActiveSkill.lock()->GetSkillIndex();

	if (SKILL_INDEX::FIRST == eSkillIndex)
	{
		if (IS_PRESS(KEY_TYPE::A))
			tChargingDuration.Update(DELTA_TIME);

		if (IS_UP(KEY_TYPE::A))
		{
			pActiveSkill.lock()->StoreChargingProgress(tChargingDuration.GetProgress());
			AddChangeStateEvent(PLAYER_STATE::SKILL);
		}
	}

	else
	{
		if (IS_PRESS(KEY_TYPE::S))
			tChargingDuration.Update(DELTA_TIME);

		if (IS_UP(KEY_TYPE::S))
		{
			pActiveSkill.lock()->StoreChargingProgress(tChargingDuration.GetProgress());
			AddChangeStateEvent(PLAYER_STATE::SKILL);
		}
	}
}

void ChargingState::Enter()
{
	PlayAnimation();

	weak_ptr<SkulSkill> pActiveSkill = m_pPlayer.lock()->GetActiveSkul()->GetActiveSkill().lock();
	tChargingDuration.SetEndTime(pActiveSkill.lock()->GetMaxChargingTime());
}

void ChargingState::Exit()
{
}

void ChargingState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::CHARGING);
}
