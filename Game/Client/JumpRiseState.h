#pragma once
#include "PlayerState.h"
class Player;
class JumpRiseState :
    public PlayerState
{
public:
    explicit JumpRiseState(shared_ptr<Player> pPlayer);
    virtual ~JumpRiseState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;

private:

};

