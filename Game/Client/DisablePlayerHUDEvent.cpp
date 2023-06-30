#include "pch.h"
#include "DisablePlayerHUDEvent.h"
#include "InterfaceManager.h"
#include "HUD.h"

DisablePlayerHUDEvent::DisablePlayerHUDEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::PLAYER_HUD_DISABLE, pConditionBlock)
{
}

DisablePlayerHUDEvent::~DisablePlayerHUDEvent()
{
}

void DisablePlayerHUDEvent::Update()
{
	DungeonEvent::Update();
}

void DisablePlayerHUDEvent::ExecuteEvent()
{
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_INTERFACE)->Disable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_HEALTH_BAR)->Disable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SECOND_SKILL_FRAME)->Disable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_FIRST)->Disable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_SECOND)->Disable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKUL_THUMNAIL)->Disable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKUL_SWAP)->Disable();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_CLOBBER)->Disable();
}
