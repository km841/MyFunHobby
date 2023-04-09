#pragma once
#include "HUD.h"
class Player;
class HealthBarHUD :
    public HUD
{
public:
    HealthBarHUD();
    virtual ~HealthBarHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    


private:
    
};

