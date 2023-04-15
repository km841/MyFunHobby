#pragma once
#include "PlayerState.h"
class AttackState :
    public PlayerState
{
public:
    explicit AttackState(shared_ptr<Player> pPlayer);
    virtual ~AttackState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override { }
};

