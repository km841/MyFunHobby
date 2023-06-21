#pragma once
#include "SkulAttack.h"
class DevilBerserkerAttack :
    public SkulAttack
{
public:
    DevilBerserkerAttack(shared_ptr<Skul> pSkul);
    virtual ~DevilBerserkerAttack();

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void CreateHitEffectAndAddedScene(Vec3 vMonsterPos) override;
};

