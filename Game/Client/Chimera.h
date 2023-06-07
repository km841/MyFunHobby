#pragma once
#include "GameObject.h"
class SpineResource;
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

    virtual void Destroy();

private:
    spine::Skeleton* m_pSkeleton;
    spine::AnimationState* m_pAnimationState;

    shared_ptr<SpineResource> m_pSpineResource;
};

