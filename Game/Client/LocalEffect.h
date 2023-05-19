#pragma once
#include "GameObject.h"
class LocalEffect :
    public GameObject
{
public:
    LocalEffect();
    virtual ~LocalEffect();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    DECLARE_POOL(LocalEffect);
};

