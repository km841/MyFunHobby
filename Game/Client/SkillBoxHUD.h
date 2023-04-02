#pragma once
#include "HUD.h"
class SkillBoxHUD :
    public HUD
{
public:
    SkillBoxHUD();
    virtual ~SkillBoxHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

};

