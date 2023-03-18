#pragma once
#include "Object.h"
class Texture;
class Animator;
class Animation :
    public Object
{
public:
    friend class Animator;
    Animation(const std::vector<FrameData> vFrameDataList);
    virtual ~Animation();

public:
    void Update();
    void SetTexture(shared_ptr<Texture> pTexture) { m_pTexture = pTexture; }
    void SetAnimator(shared_ptr<Animator> pAnimator) { m_pAnimator = pAnimator; }
    void PushData();

    void RefreshAnimation(const std::vector<FrameData> vFrameDataList);

public:
    virtual void Load(const wstring& szPath);
    virtual void Save(const wstring& szPath);

private:
    std::vector<FrameData> m_vFrameDataList;
    weak_ptr<Animator> m_pAnimator;
    shared_ptr<Texture> m_pTexture;
    int32 m_iCurFrame;
    float m_fAccTime;
    bool  m_bLoop;
    bool  m_bFinished;
};

