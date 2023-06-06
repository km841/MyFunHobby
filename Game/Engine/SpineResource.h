#pragma once
#include "Object.h"
class SpineResource :
    public Object
{
public:
    SpineResource(spine::SkeletonData* pSkeletonData);
    virtual ~SpineResource();

    void Init();

    FORCEINLINE spine::SkeletonData* GetSkeletonData() { return m_pSkeletonData; }
    FORCEINLINE spine::AnimationStateData* GetAnimationStateData() { return m_pAnimationStateData; }

private:
    spine::SkeletonData* m_pSkeletonData;
    spine::AnimationStateData* m_pAnimationStateData;
};

