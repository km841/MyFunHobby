#pragma once
#include "Player.h"
class PlayerState;
class Player;
class StateMachine
{
	using StateMap = std::map<PLAYER_STATE, shared_ptr<PlayerState>>;
public:
	StateMachine();
	virtual ~StateMachine() = default;

public:
	void Awake();
	void Update();

public:
	void SetPlayer(shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
	void ChangePlayerState(PLAYER_STATE ePlayerState);

private:
	weak_ptr<Player>	m_pPlayer;
	shared_ptr<PlayerState> m_pActiveState;
	StateMap			    m_mStateMap;


};

