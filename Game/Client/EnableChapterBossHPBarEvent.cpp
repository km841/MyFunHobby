#include "pch.h"
#include "EnableChapterBossHPBarEvent.h"
#include "InterfaceManager.h"
#include "ChapterBossHPHUD.h"

EnableChapterBossHPBarEvent::EnableChapterBossHPBarEvent(shared_ptr<ConditionBlock> pConditionBlock, STAGE_KIND eStageKind)
	: DungeonEvent(DUNGEON_EVENT_KIND::ENABLE_BOSS_HP_HUD, pConditionBlock)
	, m_eStageKind(eStageKind)
{
}

EnableChapterBossHPBarEvent::~EnableChapterBossHPBarEvent()
{
}

void EnableChapterBossHPBarEvent::Update()
{
	DungeonEvent::Update();
}

void EnableChapterBossHPBarEvent::ExecuteEvent()
{
	static_pointer_cast<ChapterBossHPHUD>(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BOSS_HP))->SetStageKind(m_eStageKind);
	static_pointer_cast<ChapterBossHPHUD>(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BOSS_HP))->Action();
}
