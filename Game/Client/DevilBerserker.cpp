#include "pch.h"
#include "DevilBerserker.h"

DevilBerserker::DevilBerserker(const SkulInfo& skulInfo)
	: Skul(skulInfo)
	, m_eBerserkerState(BERSERKER_STATE::NORMAL)
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
}

void DevilBerserker::FinalUpdate()
{
	Skul::FinalUpdate();
}
