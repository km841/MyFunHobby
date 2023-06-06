#pragma once
#include "GameObject.h"
class Chimera :
    public GameObject
{
public:
    Chimera();
    virtual ~Chimera();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    spine::Skeleton* m_pSkeleton;
    spine::AnimationState* m_pAnimationState;
};

