#pragma once

class Player;
class PlayerState
{
public:
	explicit PlayerState(shared_ptr<Player> pPlayer);
	virtual ~PlayerState() = default;

public:
	virtual void Update() { }
	bool CheckGrounded();

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

protected:
	weak_ptr<Player> m_pPlayer;
};

