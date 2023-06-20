#include "pch.h"
#include "EnableViceBossHPBarEvent.h"
#include "InterfaceManager.h"
#include "ViceBossHPHUD.h"

EnableViceBossHPBarEvent::EnableViceBossHPBarEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<Monster> pBoss)
	: DungeonEvent(DUNGEON_EVENT_KIND::ENABLE_BOSS_HP_HUD, pConditionBlock)
	, m_pBoss(pBoss)
{
}

EnableViceBossHPBarEvent::~EnableViceBossHPBarEvent()
{
}

void EnableViceBossHPBarEvent::Update()
{
	DungeonEvent::Update();
}

void EnableViceBossHPBarEvent::ExecuteEvent()
{
	static_pointer_cast<ViceBossHPHUD>(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::VICE_BOSS_HP))->SetBoss(m_pBoss.lock());
	static_pointer_cast<ViceBossHPHUD>(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::VICE_BOSS_HP))->Action();
}
