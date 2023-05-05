#include "pch.h"
#include "MonsterSpawnDungeonEvent.h"
#include "ObjectFactory.h"

MonsterSpawnDungeonEvent::MonsterSpawnDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock, MONSTER_KIND eMonsterKind, const Vec3& vMonsterPos)
	: DungeonEvent(DUNGEON_EVENT_KIND::MONSTER_SPAWN, pConditionBlock)
	, m_eMonsterKind(eMonsterKind)
	, m_vMonsterPos(vMonsterPos)
{
}

MonsterSpawnDungeonEvent::~MonsterSpawnDungeonEvent()
{
}

void MonsterSpawnDungeonEvent::Update()
{
	DungeonEvent::Update();
}

void MonsterSpawnDungeonEvent::ExecuteEvent()
{
	GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene(m_eMonsterKind, m_vMonsterPos);
}
