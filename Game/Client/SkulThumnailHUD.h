#pragma once
#include "HUD.h"

class SkulThumnailHUD :
    public HUD
{
public:
    SkulThumnailHUD();
    virtual ~SkulThumnailHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:

};

