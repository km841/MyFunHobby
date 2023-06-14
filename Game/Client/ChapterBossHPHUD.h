#pragma once
#include "HUD.h"

class Monster;
class ChapterBossHPHUD :
    public HUD
{
public:
    ChapterBossHPHUD(shared_ptr<Monster> pBoss);
    virtual ~ChapterBossHPHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Action();

    weak_ptr<Monster> GetBoss() { return m_pBoss; }
    
    void UpdateAction();

    void SetStageKind(STAGE_KIND eStageKind);

private:
    STAGE_KIND m_eStageKind;
    bool m_bAction;
    Timer m_tDuration;
    float m_fSpeed;

    weak_ptr<Monster> m_pBoss;
};

