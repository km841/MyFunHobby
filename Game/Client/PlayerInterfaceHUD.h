#pragma once
#include "HUD.h"

class Player;
class HealthBarHUD;
class SkulHeadHUD;
class PlayerInterfaceHUD :
    public HUD
{
public:
    PlayerInterfaceHUD();
    virtual ~PlayerInterfaceHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:

};

