#include "pch.h"
#include "GoToNextDungeonEvent.h"

GoToNextDungeonEvent::GoToNextDungeonEvent(shared_ptr<Stage> pStage, DUNGEON_TYPE eDungeonType)
	: m_pStage(pStage)
	, m_eDungeonType(eDungeonType)
{
	m_eEventType = EVENT_TYPE::GO_TO_NEXT_DUNGEON;
}
