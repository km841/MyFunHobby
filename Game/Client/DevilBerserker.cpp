#include "pch.h"
#include "DevilBerserker.h"
#include "Clock.h"
#include "Player.h"

DevilBerserker::DevilBerserker(const SkulInfo& skulInfo)
	: Skul(skulInfo)
	, m_eBerserkerState(BERSERKER_STATE::NORMAL)
	, m_tDemonizationTimer(20.f)
{
	SetEnumIndex(static_cast<uint8>(m_eBerserkerState));
}

void DevilBerserker::Awake()
{
	Skul::Awake();
}

void DevilBerserker::Start()
{
	Skul::Start();
}

void DevilBerserker::Update()
{
	Skul::Update();
}

void DevilBerserker::LateUpdate()
{
	Skul::LateUpdate();
	if (m_tDemonizationTimer.IsRunning())
	{
		m_tDemonizationTimer.Update(WORLD_DELTA_TIME);
		if (static_cast<uint8>(BERSERKER_STATE::DEVIL) == m_iEnumIndex && 
			m_tDemonizationTimer.IsFinished())
		{
			m_iEnumIndex = 0;
			m_tDemonizationTimer.Reset();
			m_pPlayer.lock()->RefreshAnimation();
		}
	}
}

void DevilBerserker::FinalUpdate()
{
	Skul::FinalUpdate();
}

void DevilBerserker::Demonization()
{
	m_iEnumIndex = static_cast<uint8>(BERSERKER_STATE::DEVIL);
	m_tDemonizationTimer.Start();
	m_pPlayer.lock()->RefreshAnimation();
}
