#include "pch.h"
#include "DisableChapterBossHPBarEvent.h"
#include "InterfaceManager.h"
#include "HUD.h"

DisableChapterBossHPBarEvent::DisableChapterBossHPBarEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::MONSTER_SPAWN, pConditionBlock)
{
}

DisableChapterBossHPBarEvent::~DisableChapterBossHPBarEvent()
{
}

void DisableChapterBossHPBarEvent::Update()
{
	DungeonEvent::Update();
}

void DisableChapterBossHPBarEvent::ExecuteEvent()
{
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BOSS_HP)->Disable();
}
