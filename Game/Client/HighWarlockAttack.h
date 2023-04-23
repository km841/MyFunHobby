#pragma once
#include "SkulAttack.h"
class HighWarlockAttack :
    public SkulAttack
{
public:
    HighWarlockAttack(shared_ptr<Skul> pSkul);
    virtual ~HighWarlockAttack();

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void CreateHitEffectAndAddedScene(Vec3 vMonsterPos) {}

private:
    void CreateBaseProjectileAndAddedToScene();

private:
    float m_fBaseProjectileSpeed;
};

