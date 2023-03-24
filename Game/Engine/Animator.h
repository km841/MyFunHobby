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
    void                  Update();
    void                  CreateAnimation(const std::vector<FrameData> vFrameDataList);
    void                  Play(const wstring& szName, bool bLoop = true, uint32 iSection = 0);
    
    shared_ptr<Animation> GetActiveAnimation() { return m_pActiveAnimation; }
    shared_ptr<Animation> FindAnimation(const wstring& szName);
    void                  AddAnimation(const wstring& szName, shared_ptr<Animation> pAnimation);

private:
    AnimationMap          m_mAnimations;
    shared_ptr<Animation> m_pActiveAnimation;
};

