#pragma once
#include "HUD.h"
class ChapterBossHPHUD :
    public HUD
{
public:
    ChapterBossHPHUD();
    virtual ~ChapterBossHPHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Action();
    
    void UpdateAction();

    void SetStageKind(STAGE_KIND eStageKind);

private:
    STAGE_KIND m_eStageKind;
    bool m_bAction;
    Timer m_tDuration;
    float m_fSpeed;
};

