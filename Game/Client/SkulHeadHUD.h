#pragma once
#include "HUD.h"

class SkulHeadHUD :
    public HUD
{
public:
    SkulHeadHUD();
    virtual ~SkulHeadHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:

};

