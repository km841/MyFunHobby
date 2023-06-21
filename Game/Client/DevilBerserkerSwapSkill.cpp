#include "pch.h"
#include "DevilBerserkerSwapSkill.h"
#include "Player.h"
#include "Skul.h"
#include "RigidBody.h"
#include "Clock.h"
#include "PlayerState.h"
#include "Scene.h"
#include "Scenes.h"

DevilBerserkerSwapSkill::DevilBerserkerSwapSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
	, m_bUpFinishedFlag(false)
	, m_tUpTimer(0.5f)
{
}

void DevilBerserkerSwapSkill::Update()
{
	SkulSkill::Update();

	if (!m_bUpFinishedFlag && m_tUpTimer.IsRunning())
	{
		m_tUpTimer.Update(WORLD_DELTA_TIME);

		if (m_tUpTimer.IsFinished())
		{
			m_bUpFinishedFlag = true;
			m_pSkul.lock()->GetPlayer().lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::LAND, false);

		}
		else
		{
			float fProgress = 1.f-m_tUpTimer.GetProgress();
			m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(Vec3(600.f * fProgress, 1000.f * fProgress, 0.f));
			// ���
		}
	}

	if (m_bUpFinishedFlag)
	{
		if (m_pSkul.lock()->GetPlayer().lock()->GetPlayerState().lock()->CheckGrounded())
		{
			m_bUpFinishedFlag = false;
			m_tUpTimer.Stop();
			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(0.f, 1000.f, 0.f));
		}
		else
		{
			m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(Vec3(0.f, -2000.f, 0.f));
		}
	}
}

void DevilBerserkerSwapSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void DevilBerserkerSwapSkill::Enter()
{
	m_tUpTimer.Start();
	m_pSkul.lock()->GetPlayer().lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::JUMP_RISE);
}

void DevilBerserkerSwapSkill::Exit()
{
	m_tUpTimer.Reset();
	m_bUpFinishedFlag = false;
}
