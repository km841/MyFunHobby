#include "pch.h"
#include "Ch3BossDungeon.h"

Ch3BossDungeon::Ch3BossDungeon(const wstring& szMapPath, const wstring& szScriptPath)
	: Dungeon(DUNGEON_TYPE::STAGE_BOSS, szMapPath, szScriptPath)
{
}

Ch3BossDungeon::~Ch3BossDungeon()
{
}

void Ch3BossDungeon::Awake()
{
	Dungeon::Awake();
}

void Ch3BossDungeon::Start()
{
	Dungeon::Start();
}

void Ch3BossDungeon::Update()
{
	Dungeon::Update();
}

void Ch3BossDungeon::LateUpdate()
{
	Dungeon::LateUpdate();
}

void Ch3BossDungeon::FinalUpdate()
{
	Dungeon::FinalUpdate();
}
