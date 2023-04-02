#pragma once
#include "PlayerState.h"
class AttackBState :
    public PlayerState
{
public:
    explicit AttackBState(shared_ptr<Player> pPlayer);
    virtual ~AttackBState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;
};

