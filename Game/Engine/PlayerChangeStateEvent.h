#pragma once
#include "Event.h"
#include "Player.h"
class PlayerChangeStateEvent :
    public Event
{
public:
    PlayerChangeStateEvent(shared_ptr<Player> pPlayer, PLAYER_STATE eNextPlayerState);
    FORCEINLINE PLAYER_STATE GetNextPlayerState() { return m_eNextPlayerState; }
    shared_ptr<Player> GetPlayer() { return std::move(m_pPlayer); }

public:
    PLAYER_STATE m_eNextPlayerState;
    shared_ptr<Player> m_pPlayer;
};

