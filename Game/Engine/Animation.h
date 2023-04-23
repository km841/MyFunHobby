#pragma once
#include "Object.h"
class Texture;
class Animator;
class Animation :
    public Object
{
public:
    friend class Animator;
    Animation();
    explicit Animation(const std::vector<FrameData> vFrameDataList);
    virtual ~Animation();

public:
    void Update();


    FORCEINLINE void                          SetTexture(shared_ptr<Texture> pTexture)    { m_pTexture  = pTexture; }
    FORCEINLINE shared_ptr<Texture>           GetTexture()                                { return m_pTexture; }
    FORCEINLINE void                          SetAnimator(shared_ptr<Animator> pAnimator) { m_pAnimator = pAnimator; }
    FORCEINLINE bool                          IsFinished()                                { return m_bFinished; }
    FORCEINLINE const std::vector<FrameData>& GetFrameDataList()                          { return m_vFrameDataList; }
    FORCEINLINE int32                         GetCurFrame()                               { return m_iCurFrame; }
    FORCEINLINE int32                         GetHitFrame()                               { return m_iHitFrame; }
    FORCEINLINE bool                          IsHitFrame()                                { return !m_bHitChecked && m_iCurFrame == m_iHitFrame; }
    FORCEINLINE void                          CheckToHitFrame()                           { m_bHitChecked = true; }
    
    void SetTriggerFrame(int32 iTriggerFrame);
    void CheckToTriggerFrame();
    bool IsTriggerFrame();

    void  SetHitFrame(int32 iHitFrame);
    float GetAnimationProgress();
    void  Reset();
    void  PushData();
    void  RefreshAnimation(const std::vector<FrameData> vFrameDataList);

public:
    virtual void Load(const wstring& szPath);
    virtual void Save(const wstring& szPath);

private:
    std::vector<FrameData>  m_vFrameDataList;
    weak_ptr<Animator>      m_pAnimator;
    shared_ptr<Texture>     m_pTexture;
    int32                   m_iCurFrame;
    int32                   m_iSection;
    float                   m_fAccTime;
    bool                    m_bLoop;
    bool                    m_bFinished;
    int32                   m_iHitFrame;

    std::vector<bool>       m_vTriggerFrames;
    std::vector<bool>       m_vTriggerChecked;

    // 한 프레임 당 Hit 이벤트가 어러 번 체크되지 않도록 하는 플래그
    bool                    m_bHitChecked;
};

