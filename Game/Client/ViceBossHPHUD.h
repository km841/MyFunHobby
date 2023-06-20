#pragma once
#include "HUD.h"
class Monster;
class ViceBossHPHUD :
    public HUD
{
public:
    ViceBossHPHUD();
    virtual ~ViceBossHPHUD();

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

private:
    void CreateHPHUDAndAddedToScene();

private:
    bool m_bAction;
    Timer m_tDuration;
    float m_fSpeed;

    weak_ptr<Monster> m_pBoss;
    weak_ptr<HUD> m_pHPHUD;
};

