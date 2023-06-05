#pragma once
#include "PlayerState.h"
class PauseIdleState :
    public PlayerState
{
public:
    explicit PauseIdleState(shared_ptr<Player> pPlayer);
    virtual ~PauseIdleState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;
};

