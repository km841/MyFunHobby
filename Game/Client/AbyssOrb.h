#pragma once
#include "PlayerProjectile.h"
class AbyssOrb :
    public PlayerProjectile
{
public:
    AbyssOrb();
    virtual ~AbyssOrb();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    Timer m_tLifeTimer;
    bool m_bCompleted;
    bool m_bDespawn;

    Timer m_tDamageTick;
};

