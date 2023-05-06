#include "pch.h"
#include "BlackLab.h"
#include "BaseCamp.h"
#include "BoneDungeon.h"

BlackLab::BlackLab()
	: Stage(STAGE_KIND::BLACK_LAB)
{
}

BlackLab::~BlackLab()
{
}

void BlackLab::Awake()
{
	// Add dungeons
	AddDungeon(make_shared<BaseCamp>(L"..\\Resources\\Map\\BaseCampMap2.map"));
	AddDungeon(make_shared<BoneDungeon>(L"..\\Resources\\Map\\Ch3Map6.map"));
	// Awaken all stages and select the active dungeon.
	Stage::Awake();
}

void BlackLab::Start()
{
	Stage::Start();
}

void BlackLab::Update()
{
	Stage::Update();
}

void BlackLab::LateUpdate()
{
	Stage::LateUpdate();
}

void BlackLab::FinalUpdate()
{
	Stage::FinalUpdate();
}

void BlackLab::Enter()
{
	Awake();
	m_pActiveDungeon.lock()->Enter();
}

void BlackLab::Exit()
{
	m_pActiveDungeon.lock()->Exit();
}
