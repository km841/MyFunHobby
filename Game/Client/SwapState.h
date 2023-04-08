#pragma once
#include "PlayerState.h"
class Player;
class SwapState :
    public PlayerState
{
public:
    explicit SwapState(shared_ptr<Player> pPlayer);
    virtual ~SwapState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;

private:
};

