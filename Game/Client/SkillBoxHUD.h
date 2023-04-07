#pragma once
#include "HUD.h"
class InterfaceEffect;
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

private:
    void CreateAndAddCompletionEffectToScene();

public:
    weak_ptr<InterfaceEffect> GetCompletionEffect() { return m_pCompletionEffect; }

private:
    shared_ptr<InterfaceEffect> m_pCompletionEffect;

};

