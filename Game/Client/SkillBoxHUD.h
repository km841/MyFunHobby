#pragma once
#include "HUD.h"
class InterfaceEffect;
class Player;
class SkillBoxHUD :
    public HUD
{
public:
    SkillBoxHUD(SKILL_INDEX eSkillIndex);
    virtual ~SkillBoxHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Enable();
    virtual void Disable();

private:
    void CreateAndAddCompletionEffectToScene();
    void CreateHotKeyHUDAndAddedToScene();

public:
    weak_ptr<InterfaceEffect>    GetCompletionEffect() { return m_pCompletionEffect; }
    void PlayCompletionAnimation();

private:
    shared_ptr<InterfaceEffect> m_pCompletionEffect;
    shared_ptr<HUD> m_pHotKeyHUD;

    SKILL_INDEX m_eSkillIndex;
};

