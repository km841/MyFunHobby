#include "pch.h"
#include "PauseDungeonEvent.h"
#include "Clock.h"

PauseDungeonEvent::PauseDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::PAUSE, pConditionBlock)
{
}

PauseDungeonEvent::~PauseDungeonEvent()
{
}

void PauseDungeonEvent::Update()
{
	DungeonEvent::Update();
}

void PauseDungeonEvent::ExecuteEvent()
{
	GET_SINGLE(Clock)->Pause();
}