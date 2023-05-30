#pragma once
#include "HUD.h"
class DropItemHUD :
    public HUD
{
public:
    DropItemHUD();
    virtual ~DropItemHUD();

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

