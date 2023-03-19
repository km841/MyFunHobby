#include "pch.h"
#include "PlayerChangeStateEvent.h"

PlayerChangeStateEvent::PlayerChangeStateEvent(shared_ptr<Player> pPlayer, PLAYER_STATE eNextPlayerState)
	:m_eNextPlayerState(eNextPlayerState)
	,m_pPlayer(pPlayer)
{
	m_eEventType = EVENT_TYPE::PLAYER_CHANGE_STATE;
}
