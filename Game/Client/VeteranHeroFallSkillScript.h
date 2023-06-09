#pragma once
#include "MonoBehaviour.h"
class VeteranHeroFallSkillScript :
    public MonoBehaviour
{
public:
    VeteranHeroFallSkillScript();
    virtual ~VeteranHeroFallSkillScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateJumpSmokeAndAddedToScene();
    void CreateWarningSignAndAddedToScene();
    void CreateMagicSwordsAndAddedToScene();

private:
    bool m_bSkillReadyFlag;
    bool m_bSkillFlag;
    bool m_bWarningSignFlag;
    Timer m_tDelayTime;
    Timer m_tFallStayTime;
    Vec3 m_vFallDownPos;
};

