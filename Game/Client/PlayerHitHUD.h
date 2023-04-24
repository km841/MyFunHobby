#pragma once
#include "HUD.h"
class PlayerHitHUD :
    public HUD
{
public:
    PlayerHitHUD();
    virtual ~PlayerHitHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    void PlayHitAnimation();
};

