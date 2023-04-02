#pragma once
#include "PlayerState.h"
class JumpAttackState :
    public PlayerState
{
public:
    explicit JumpAttackState(shared_ptr<Player> pPlayer);
    virtual ~JumpAttackState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;

private:
};

