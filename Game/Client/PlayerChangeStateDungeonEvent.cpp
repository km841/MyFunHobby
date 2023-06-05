#include "pch.h"
#include "PlayerChangeStateDungeonEvent.h"
#include "PlayerChangeStateEvent.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Scene.h"
#include "Player.h"

PlayerChangeStateDungeonEvent::PlayerChangeStateDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock, PLAYER_STATE eNextPlayerState)
	: DungeonEvent(DUNGEON_EVENT_KIND::PLAYER_STATE_CHANGE, pConditionBlock)
	, m_eNextPlayerState(eNextPlayerState)
{
}

PlayerChangeStateDungeonEvent::~PlayerChangeStateDungeonEvent()
{
}

void PlayerChangeStateDungeonEvent::Update()
{
	DungeonEvent::Update();
}

void PlayerChangeStateDungeonEvent::ExecuteEvent()
{
	GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer(), m_eNextPlayerState));
}
