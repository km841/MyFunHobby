#include "pch.h"
#include "MonsterChangeStateDungeonEvent.h"
#include "MonsterChangeStateEvent.h"
#include "EventManager.h"

MonsterChangeStateDungeonEvent::MonsterChangeStateDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<Monster> pMonster, MONSTER_STATE eNextState)
	:DungeonEvent(DUNGEON_EVENT_KIND::MONSTER_STATE_CHANGE, pConditionBlock)
	, m_pMonster(pMonster)
	, m_eNextState(eNextState)
{
}

MonsterChangeStateDungeonEvent::~MonsterChangeStateDungeonEvent()
{
}

void MonsterChangeStateDungeonEvent::Update()
{
	DungeonEvent::Update();
}

void MonsterChangeStateDungeonEvent::ExecuteEvent()
{
	GET_SINGLE(EventManager)->AddEvent(make_unique<MonsterChangeStateEvent>(m_pMonster.lock(), m_eNextState));
}
