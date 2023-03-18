#pragma once
#include "Component.h"

class Texture;
class Animation;

class Animator :
      public Component
    , public std::enable_shared_from_this<Animator>
{
    using AnimationMap = std::map<wstring, shared_ptr<Animation>>;
public:
    Animator();
    virtual ~Animator();

public:
    void Update();
    void CreateAnimation(const std::vector<FrameData> vFrameDataList);
    void Play(const wstring& szAnimName, bool bLoop = true);

    shared_ptr<Animation> GetCurAnimation() { return m_pCurAnimation; }

private:
    AnimationMap m_mAnimations;
    shared_ptr<Animation> m_pCurAnimation;
};

