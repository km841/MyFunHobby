#include "pch.h"
#include "PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(shared_ptr<Player> pPlayer)
	:m_pPlayer(pPlayer)
{
}
