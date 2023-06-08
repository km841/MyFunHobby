#pragma once
#include "HUD.h"
class BossOpeningHUD :
    public HUD
{
public:
    BossOpeningHUD();
    virtual ~BossOpeningHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Action();

    void SetStageKind(STAGE_KIND eStageKind);

private:
    STAGE_KIND m_eStageKind;
    bool m_bAction;
    Timer m_tDuration;
    Timer m_tStayTimer;

};

