#pragma once
#include "PlayerState.h"
class SkillState :
    public PlayerState
{
public:
    explicit SkillState(shared_ptr<Player> pPlayer);
    virtual ~SkillState() = default;


public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;

private:
};

