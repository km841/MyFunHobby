#pragma once
#include "GameObject.h"
class AnimationLocalEffectOtherLayer :
    public GameObject
{
public:
    AnimationLocalEffectOtherLayer();
    virtual ~AnimationLocalEffectOtherLayer();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    DECLARE_POOL(AnimationLocalEffectOtherLayer);
};

