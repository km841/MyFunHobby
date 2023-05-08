#include "pch.h"
#include "Dungeon_Bone.h"
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

Dungeon_Bone::Dungeon_Bone(const wstring& szMapPath, const wstring& szScriptPath)
	: Dungeon(DUNGEON_TYPE::DUNGEON_BONE, szMapPath, szScriptPath)
{
}

Dungeon_Bone::~Dungeon_Bone()
{
}

void Dungeon_Bone::Awake()
{
	Dungeon::Awake();
}

void Dungeon_Bone::Start()
{
	Dungeon::Start();
}

void Dungeon_Bone::Update()
{
	Dungeon::Update();
}

void Dungeon_Bone::LateUpdate()
{
	Dungeon::LateUpdate();
}

void Dungeon_Bone::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void Dungeon_Bone::Enter()
{
	Dungeon::Enter();
}

void Dungeon_Bone::Exit()
{
	Dungeon::Exit();
}
