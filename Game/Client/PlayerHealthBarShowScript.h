#pragma once
#include "MonoBehaviour.h"
class Player;
class HealthBarHUD;
class PlayerHealthBarShowScript :
    public MonoBehaviour
{
public:
    explicit PlayerHealthBarShowScript(shared_ptr<HealthBarHUD> pHealthBar);
    virtual ~PlayerHealthBarShowScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<HealthBarHUD> m_pHealthBar;
    float m_fPrevHP;
    float m_fDiff;
};

