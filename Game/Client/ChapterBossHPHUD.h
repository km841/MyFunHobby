#pragma once
#include "HUD.h"

class Monster;
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
    virtual void Destroy();

    virtual void Action();

    virtual void Enable();
    virtual void Disable();

    void              SetBoss(shared_ptr<Monster> pMonster) { m_pBoss = pMonster; }
    weak_ptr<Monster> GetBoss() { return m_pBoss; }
    
    void UpdateAction();

    void SetStageKind(STAGE_KIND eStageKind);

private:
    void CreateHPHUDAndAddedToScene();

private:
    STAGE_KIND m_eStageKind;
    bool m_bAction;
    Timer m_tDuration;
    float m_fSpeed;

    weak_ptr<Monster> m_pBoss;
    weak_ptr<HUD> m_pHPHUD;
};

