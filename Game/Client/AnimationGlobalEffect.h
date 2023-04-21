#pragma once
#include "GlobalEffect.h"
class AnimationGlobalEffect :
    public GlobalEffect
{
public:
    AnimationGlobalEffect();
    virtual ~AnimationGlobalEffect();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    DECLARE_POOL(AnimationGlobalEffect);
};

