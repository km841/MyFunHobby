#include "pch.h"
#include "LittleBone.h"

LittleBone::LittleBone()
	: Skul(SKUL_GRADE::NORMAL)
	, m_bHasHead(true)
{
}

void LittleBone::Awake()
{
	Skul::Awake();
}

void LittleBone::Start()
{
	Skul::Start();
}

void LittleBone::Update()
{
	Skul::Update();
}

void LittleBone::LateUpdate()
{
	Skul::LateUpdate();
}

void LittleBone::FinalUpdate()
{
	Skul::FinalUpdate();
}
