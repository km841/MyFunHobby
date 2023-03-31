#pragma once
#include "Player.h"

class PlayerState
{
public:
	explicit PlayerState(shared_ptr<Player> pPlayer);
	virtual ~PlayerState() = default;

public:
	virtual void Awake()  { }
	virtual void Update() { }
	bool CheckGrounded();
	void AddChangeStateEvent(PLAYER_STATE ePlayerState);

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

protected:
	weak_ptr<Player> m_pPlayer;
};

