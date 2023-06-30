#pragma once
#include "HUD.h"
class SwapSkulHUD :
    public HUD
{
public:
    SwapSkulHUD();
    virtual ~SwapSkulHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Enable();
    virtual void Disable();

private:
    void CreateSpaceKeyHUDAndAddedToScene();

private:
    weak_ptr<HUD> m_pSpaceHUD;
};

