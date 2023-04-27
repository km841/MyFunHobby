#pragma once
#include "HUD.h"
class MousePointerHUD :
    public HUD
{
public:
    MousePointerHUD();
    virtual ~MousePointerHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

