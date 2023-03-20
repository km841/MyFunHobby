#pragma once

class Player;
class PlayerState
{
public:
	PlayerState(shared_ptr<Player> pPlayer);
	virtual ~PlayerState() = default;

public:
	virtual void Update() { }

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

protected:
	weak_ptr<Player> m_pPlayer;
};

