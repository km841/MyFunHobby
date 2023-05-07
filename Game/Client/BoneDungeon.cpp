#include "pch.h"
#include "BoneDungeon.h"
#include "Scene.h"
#include "Scenes.h"
#include "Engine.h"
#include "EventManager.h"
#include "ObjectFactory.h"
#include "JuniorKnight.h"
#include "IfAllDeadMonsterInDungeon.h"
#include "MonsterSpawnDungeonEvent.h"
#include "IfAlwaysTrue.h"
#include "PlayerTeleportEvent.h"

BoneDungeon::BoneDungeon(const wstring& szMapPath, const wstring& szScriptPath)
	: Dungeon(DUNGEON_TYPE::DUNGEON_BONE, szMapPath, szScriptPath)
{
}

BoneDungeon::~BoneDungeon()
{
}

void BoneDungeon::Awake()
{
	Dungeon::Awake();
}

void BoneDungeon::Start()
{
	Dungeon::Start();
}

void BoneDungeon::Update()
{
	Dungeon::Update();
}

void BoneDungeon::LateUpdate()
{
	Dungeon::LateUpdate();
}

void BoneDungeon::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void BoneDungeon::Enter()
{
	Dungeon::Enter();
}

void BoneDungeon::Exit()
{
	Dungeon::Exit();
}
