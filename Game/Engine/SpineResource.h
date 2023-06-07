#pragma once
#include "Object.h"
class SpineResource :
    public Object
{
public:
    SpineResource(const string& szAtlasPath, const string& szBinaryPath);
    virtual ~SpineResource();
    virtual void Destroy();

    void Init();

    FORCEINLINE spine::SkeletonData* GetSkeletonData() { return m_pSkeletonData; }
    FORCEINLINE spine::AnimationStateData* GetAnimationStateData() { return m_pAnimationStateData; }

private:
    spine::Atlas* m_pAtlas;
    spine::SkeletonData* m_pSkeletonData;
    spine::AnimationStateData* m_pAnimationStateData;
    spine::TextureLoader* m_pTextureLoader;
};

