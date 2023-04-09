#pragma once
#include "HUD.h"

class InterfaceEffect;
class Player;
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
    void                      CreateAndAddCompletionEffectToScene();

public:
    weak_ptr<InterfaceEffect> GetCompletionEffect() { return m_pCompletionEffect; }

private:
    shared_ptr<InterfaceEffect> m_pCompletionEffect;

};

