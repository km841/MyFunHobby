#pragma once
#include "DungeonEvent.h"
class Monster;
class MonsterChangeStateDungeonEvent :
    public DungeonEvent
{
public:
	MonsterChangeStateDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<Monster> pMonster, MONSTER_STATE eNextState);
	virtual ~MonsterChangeStateDungeonEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	weak_ptr<Monster> m_pMonster;
	MONSTER_STATE m_eNextState;
};

