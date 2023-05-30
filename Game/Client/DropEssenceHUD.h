#pragma once
#include "HUD.h"
class DropEssenceHUD :
    public HUD
{
public:
    DropEssenceHUD();
    virtual ~DropEssenceHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Action();

private:
    int8 m_iExitCount;
};

