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

BoneDungeon::BoneDungeon(const wstring& szMapPath)
	: Dungeon(DUNGEON_TYPE::DUNGEON_BONE, szMapPath)
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
	GET_SINGLE(Scenes)->GetActiveScene()->Load(m_szMapPath);

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	shared_ptr<IfAlwaysTrue> pAlwaysTrue = make_shared<IfAlwaysTrue>();
	AddEvent(make_shared<PlayerTeleportEvent>(pAlwaysTrue, Vec3(fWidth / 2.f + 300.f, fHeight / 2.f - 200.f, 100.f)));

	shared_ptr<IfAllDeadMonsterInDungeon> pCondition = make_shared<IfAllDeadMonsterInDungeon>();
	AddEvent(make_shared<MonsterSpawnDungeonEvent>(pCondition, MONSTER_KIND::JUNIOR_KNIGHT, Vec3(fWidth / 2.f + 300.f, fHeight / 2.f - 200.f, 99.5f)));
	AddEvent(make_shared<MonsterSpawnDungeonEvent>(pCondition, MONSTER_KIND::JUNIOR_KNIGHT, Vec3(fWidth / 2.f + 600.f, fHeight / 2.f - 200.f, 99.5f)));
}

void BoneDungeon::Exit()
{
	GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::TILE);
	GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::BACKGROUND);
	GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::DUNGEON_GATE);
}
