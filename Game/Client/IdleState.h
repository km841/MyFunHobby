#pragma once
#include "PlayerState.h"
class GameObject;
class IdleState :
    public PlayerState
{
public:
    IdleState(shared_ptr<Player> pPlayer);
    virtual ~IdleState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;

private:


};

