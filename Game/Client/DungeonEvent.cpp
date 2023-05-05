#include "pch.h"
#include "DungeonEvent.h"
#include "ConditionBlock.h"

DungeonEvent::DungeonEvent(DUNGEON_EVENT_KIND eEventKind, shared_ptr<ConditionBlock> pConditionBlock)
	: m_eEventKind(eEventKind)
	, m_pConditionBlock(pConditionBlock)
	, m_bIsTrigger(false)
{
}

DungeonEvent::~DungeonEvent()
{
}

void DungeonEvent::Update()
{
	if (m_pConditionBlock->IsTrigger())
	{
		ExecuteEvent();
		m_bIsTrigger = true;
	}
}
