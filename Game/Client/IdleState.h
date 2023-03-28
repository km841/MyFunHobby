#pragma once
#include "PlayerState.h"
class Player;
class IdleState :
    public PlayerState
{
public:
    explicit IdleState(shared_ptr<Player> pPlayer);
    virtual ~IdleState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;

private:


};

