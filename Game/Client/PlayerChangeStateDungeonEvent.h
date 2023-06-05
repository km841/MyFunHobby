#pragma once
#include "DungeonEvent.h"
class PlayerChangeStateDungeonEvent :
    public DungeonEvent
{
public:
	PlayerChangeStateDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock, PLAYER_STATE eNextPlayerState);
	virtual ~PlayerChangeStateDungeonEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	PLAYER_STATE m_eNextPlayerState;
};

