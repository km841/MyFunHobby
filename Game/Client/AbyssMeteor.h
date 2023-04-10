#pragma once
#include "PlayerProjectile.h"
class AbyssMeteor :
    public PlayerProjectile
{
public:
    AbyssMeteor();
    virtual ~AbyssMeteor();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

