#pragma once
#include "PlayerState.h"
class PauseWalkState :
    public PlayerState
{
public:
    explicit PauseWalkState(shared_ptr<Player> pPlayer);
    virtual ~PauseWalkState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;
};

