#pragma once
#include "DungeonEvent.h"
class Monster;
class EnableViceBossHPBarEvent :
    public DungeonEvent
{
public:
	EnableViceBossHPBarEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<Monster> pBoss);
	virtual ~EnableViceBossHPBarEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	weak_ptr<Monster> m_pBoss;
};

