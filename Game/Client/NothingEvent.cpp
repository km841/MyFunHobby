#include "pch.h"
#include "NothingEvent.h"

NothingEvent::NothingEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::NOTHING, pConditionBlock)
{
}

NothingEvent::~NothingEvent()
{
}

void NothingEvent::Update()
{
	DungeonEvent::Update();
}

void NothingEvent::ExecuteEvent()
{
	// Nothing
}
