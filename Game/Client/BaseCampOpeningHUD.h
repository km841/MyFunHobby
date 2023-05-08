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

private:
    Timer m_tDuration;
    float m_fInitSpeed;
};

