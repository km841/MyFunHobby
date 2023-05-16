#pragma once
#include "HUD.h"
class PlayerSecondSkillFrameHUD :
    public HUD
{
public:
    PlayerSecondSkillFrameHUD();
    virtual ~PlayerSecondSkillFrameHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

