#pragma once
#include "HUD.h"
class BaseCampOpeningHUD :
    public HUD
{
public:
    BaseCampOpeningHUD();
    virtual ~BaseCampOpeningHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Action();
    void UpdateAction();

private:
    Timer m_tStayTimer;
    Timer m_tUpTimer;
    Timer m_tDownTimer;
    float m_fSpeed;
    float m_fHudSpeed;
    bool m_bActionFlag;
};

