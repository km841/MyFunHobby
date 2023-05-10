#include "pch.h"
#include "BlackLab.h"
#include "Ch3BaseCamp.h"
#include "Dungeon_Bone.h"

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
	AddDungeon(make_shared<Ch3BaseCamp>(L"..\\Resources\\Map\\Ch3BaseCampMap.map"));
	AddDungeon(make_shared<Dungeon_Bone>(L"..\\Resources\\Map\\Ch3Map.map", L"..\\Resources\\Script\\test3.evtscript"));

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
