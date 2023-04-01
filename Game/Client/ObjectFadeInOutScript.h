#pragma once
#include "MonoBehaviour.h"
class ObjectFadeInOutScript :
    public MonoBehaviour
{
public:
    ObjectFadeInOutScript(float fDuration, FADE_TYPE eFadeType, float fStayTime = 0.f);
    virtual ~ObjectFadeInOutScript();

public:
    virtual void LateUpdate() override;

private:
    FADE_TYPE m_eFadeType;
    Timer     m_tStayTime;
    Timer     m_tDuration;
};

