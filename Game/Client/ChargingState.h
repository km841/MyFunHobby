#pragma once
#include "PlayerState.h"
class ChargingState :
    public PlayerState
{
public:
    explicit ChargingState(shared_ptr<Player> pPlayer);
    virtual ~ChargingState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;

private:
    Timer tChargingDuration;
};

