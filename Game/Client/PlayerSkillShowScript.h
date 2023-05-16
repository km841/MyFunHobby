#pragma once
#include "MonoBehaviour.h"
class Player;
class SkillBoxHUD;
class PlayerSkillShowScript :
    public MonoBehaviour
{
public:
    explicit PlayerSkillShowScript(shared_ptr<SkillBoxHUD> pHUD, SKILL_INDEX eSkillIndex);
    virtual ~PlayerSkillShowScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<SkillBoxHUD> m_pHUD;
    bool m_bPrevFlag;
    bool m_bFlag;

    SKILL_INDEX m_eSkillIndex;
};

