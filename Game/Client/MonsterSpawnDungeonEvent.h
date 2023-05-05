#pragma once
#include "DungeonEvent.h"
class MonsterSpawnDungeonEvent :
    public DungeonEvent
{
public:
	MonsterSpawnDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock, MONSTER_KIND eMonsterKind, const Vec3& vMonsterPos);
	virtual ~MonsterSpawnDungeonEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	MONSTER_KIND m_eMonsterKind;
	Vec3 m_vMonsterPos;
};

