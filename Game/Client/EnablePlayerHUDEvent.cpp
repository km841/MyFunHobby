#include "pch.h"
#include "EnablePlayerHUDEvent.h"
#include "InterfaceManager.h"
#include "HUD.h"

EnablePlayerHUDEvent::EnablePlayerHUDEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::PLAYER_HUD_ENABLE, pConditionBlock)
{
}

EnablePlayerHUDEvent::~EnablePlayerHUDEvent()
{
}

void EnablePlayerHUDEvent::Update()
{
	DungeonEvent::Update();
}

void EnablePlayerHUDEvent::ExecuteEvent()
{
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_INTERFACE)->Enable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_HEALTH_BAR)->Enable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SECOND_SKILL_FRAME)->Enable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_FIRST)->Enable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_SECOND)->Enable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKUL_THUMNAIL)->Enable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKUL_SWAP)->Enable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_CLOBBER)->Enable();
}
