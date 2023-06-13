#include "pch.h"
#include "PlayDungeonEvent.h"
#include "Clock.h"

PlayDungeonEvent::PlayDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::PLAY, pConditionBlock)
{
}

PlayDungeonEvent::~PlayDungeonEvent()
{
}

void PlayDungeonEvent::Update()
{
	DungeonEvent::Update();
}

void PlayDungeonEvent::ExecuteEvent()
{
	GET_SINGLE(Clock)->Play();
}
