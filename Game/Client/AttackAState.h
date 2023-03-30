#pragma once
#include "PlayerState.h"

class AttackAState :
    public PlayerState
{
public:
    explicit AttackAState(shared_ptr<Player> pPlayer);
    virtual ~AttackAState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
};

