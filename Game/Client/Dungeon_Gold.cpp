#include "pch.h"
#include "Dungeon_Gold.h"

Dungeon_Gold::Dungeon_Gold(const wstring& szMapPath, const wstring& szScriptPath)
	: Dungeon(DUNGEON_TYPE::DUNGEON_GOLD, szMapPath, szScriptPath)
{
}

Dungeon_Gold::~Dungeon_Gold()
{
}

void Dungeon_Gold::Awake()
{
	Dungeon::Awake();
}

void Dungeon_Gold::Start()
{
	Dungeon::Start();
}

void Dungeon_Gold::Update()
{
	Dungeon::Update();
}

void Dungeon_Gold::LateUpdate()
{
	Dungeon::LateUpdate();
}

void Dungeon_Gold::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void Dungeon_Gold::Enter()
{
	Dungeon::Enter();
}

void Dungeon_Gold::Exit()
{
	Dungeon::Exit();
}