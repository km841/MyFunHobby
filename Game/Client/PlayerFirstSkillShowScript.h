#pragma once
#include "MonoBehaviour.h"
class Player;
class SkillBoxHUD;
class PlayerFirstSkillShowScript :
    public MonoBehaviour
{
public:
    explicit PlayerFirstSkillShowScript(shared_ptr<SkillBoxHUD> pHUD);
    virtual ~PlayerFirstSkillShowScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<SkillBoxHUD> m_pHUD;
    bool m_bPrevFlag;
    bool m_bFlag;
};

