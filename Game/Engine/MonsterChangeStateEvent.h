#pragma once
#include "Event.h"
class Monster;
class MonsterChangeStateEvent :
    public Event
{
public:
    MonsterChangeStateEvent(shared_ptr<Monster> pMonster, MONSTER_STATE eNextMonsterState);
    FORCEINLINE MONSTER_STATE       GetNextMonsterState() { return m_eNextMonsterState; }
    FORCEINLINE shared_ptr<Monster> GetMonster() { return std::move(m_pMonster); }

public:
    MONSTER_STATE m_eNextMonsterState;
    shared_ptr<Monster> m_pMonster;
};

