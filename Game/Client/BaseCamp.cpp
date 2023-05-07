#include "pch.h"
#include "BaseCamp.h"
#include "Engine.h"
#include "EventManager.h"
#include "ObjectFactory.h"
#include "JuniorKnight.h"
#include "IfAllDeadMonsterInDungeon.h"
#include "MonsterSpawnDungeonEvent.h"

BaseCamp::BaseCamp(const wstring& szMapPath)
	: Dungeon(DUNGEON_TYPE::BASE_CAMP, szMapPath)
{
}

BaseCamp::~BaseCamp()
{
}

void BaseCamp::Awake()
{
	Dungeon::Awake();
}

void BaseCamp::Start()
{
	Dungeon::Start();
}

void BaseCamp::Update()
{
	Dungeon::Update();
}

void BaseCamp::LateUpdate()
{
	Dungeon::LateUpdate();
}

void BaseCamp::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void BaseCamp::Enter()
{
	Dungeon::Enter();
}

void BaseCamp::Exit()
{
	Dungeon::Exit();
}
