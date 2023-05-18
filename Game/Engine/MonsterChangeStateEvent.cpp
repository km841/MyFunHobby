#include "pch.h"
#include "MonsterChangeStateEvent.h"

MonsterChangeStateEvent::MonsterChangeStateEvent(shared_ptr<Monster> pMonster, MONSTER_STATE eNextMonsterState)
	: m_pMonster(pMonster)
	, m_eNextMonsterState(eNextMonsterState)
{
	m_eEventType = EVENT_TYPE::MONSTER_CHANGE_STATE;
}
