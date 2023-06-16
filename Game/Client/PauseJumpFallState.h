#pragma once
#include "PlayerState.h"
class PauseJumpFallState :
    public PlayerState
{
public:
    explicit PauseJumpFallState(shared_ptr<Player> pPlayer);
    virtual ~PauseJumpFallState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;
};

