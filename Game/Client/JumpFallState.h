#pragma once
#include "PlayerState.h"
class Player;
class JumpFallState :
    public PlayerState
{
public:
    JumpFallState(shared_ptr<Player> pPlayer);
    virtual ~JumpFallState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;

private:
};

