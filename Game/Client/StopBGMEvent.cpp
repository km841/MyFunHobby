#include "pch.h"
#include "StopBGMEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "Sound.h"
#include "SoundSource.h"
#include "ComponentObject.h"

StopBGMEvent::StopBGMEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::STOP_BGM, pConditionBlock)
{
}

StopBGMEvent::~StopBGMEvent()
{
}

void StopBGMEvent::Update()
{
	DungeonEvent::Update();
}

void StopBGMEvent::ExecuteEvent()
{
	SCENE_SOUND->StopBGM();
}
