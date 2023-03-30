#pragma once
#include "PlayerState.h"
class DashState :
    public PlayerState
{
public:
    explicit DashState(shared_ptr<Player> pPlayer);
    virtual ~DashState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;

private:
};

