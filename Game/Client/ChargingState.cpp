#include "pch.h"
#include "ChargingState.h"
#include "Clock.h"
#include "Input.h"
#include "SkulSkill.h"
#include "RigidBody.h"
#include "ComponentObject.h"
#include "SoundSource.h"
#include "Scenes.h"
#include "Scene.h"
#include "Resources.h"

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
		{
			tChargingDuration.Update(OBJECT_DELTA_TIME);
			pActiveSkill.lock()->StoreChargingProgress(tChargingDuration.GetProgress());
		}

		if (IS_UP(KEY_TYPE::A))
		{
			AddChangeStateEvent(PLAYER_STATE::SKILL);
		}
	}

	else
	{
		if (IS_PRESS(KEY_TYPE::S))
		{
			tChargingDuration.Update(OBJECT_DELTA_TIME);
			pActiveSkill.lock()->StoreChargingProgress(tChargingDuration.GetProgress());
		}

		if (IS_UP(KEY_TYPE::S))
		{
			AddChangeStateEvent(PLAYER_STATE::SKILL);
		}
	}

	if (IS_NONE(KEY_TYPE::LEFT) && IS_NONE(KEY_TYPE::RIGHT))
	{
		m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::X, 0.f);
	}


	if (CheckGrounded())
	{
		m_pPlayer.lock()->GetRigidBody()->RemoveGravity();
		m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	}
}

void ChargingState::Enter()
{
	PlayAnimation();

	weak_ptr<SkulSkill> pActiveSkill = m_pPlayer.lock()->GetActiveSkul()->GetActiveSkill().lock();
	tChargingDuration.SetEndTime(pActiveSkill.lock()->GetMaxChargingTime());
	tChargingDuration.Start();
	m_pPlayer.lock()->GetStatus()->fSpeed /= 2.f;

	shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"HighWarlock_Charge_Start", L"..\\Resources\\Sound\\HighWarlock_Charge_Start.wav");
	SCENE_SOUND->SetClip(pSound);
	SCENE_SOUND->Play();
}

void ChargingState::Exit()
{
	m_pPlayer.lock()->GetStatus()->fSpeed *= 2.f;
}

void ChargingState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::CHARGING);
}
