#pragma once
#include "MonoBehaviour.h"
class LocalEffect;
class ErodedEntSkillScript :
    public MonoBehaviour
{
public:
    ErodedEntSkillScript();
    virtual ~ErodedEntSkillScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateSkillSignAndAddedToScene();
    void CreateSkillEffectAndAddedToScene();


private:
    bool m_bSkillFlag;
    bool m_bSkillSignFlag;
    Vec3 m_vPlayerPos;
};

