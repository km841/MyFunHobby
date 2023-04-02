#pragma once
#include "PlayerState.h"
class Player;
class WalkState :
    public PlayerState
{
public:
    explicit WalkState(shared_ptr<Player> pPlayer);
    virtual ~WalkState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;

private:
};

