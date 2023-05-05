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
	GET_SINGLE(Scenes)->GetActiveScene()->Load(m_szMapPath);

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	// 이동시켜주는 오브젝트 (상호작용)
	// Create Monster
	{
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f - 600.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f - 300.f, fHeight / 2.f - 200.f, 99.5f));
		//GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f, fHeight / 2.f - 200.f, 99.5f));
		//GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 300.f, fHeight / 2.f - 200.f, 99.5f));
		//GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 600.f, fHeight / 2.f - 200.f, 99.5f));
	}

	shared_ptr<IfAllDeadMonsterInDungeon> pCondition = make_shared<IfAllDeadMonsterInDungeon>();
	AddEvent(make_shared<MonsterSpawnDungeonEvent>(pCondition, MONSTER_KIND::JUNIOR_KNIGHT, Vec3(fWidth / 2.f - 600.f, fHeight / 2.f - 200.f, 99.5f)));
}

void BaseCamp::Exit()
{
}
