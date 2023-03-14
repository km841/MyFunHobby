#pragma once
#include "MonoBehaviour.h"
class FadeInOutScript :
    public MonoBehaviour
{
public:
    FadeInOutScript();
    virtual ~FadeInOutScript();


public:
    virtual void LateUpdate() override;

private:
    float m_fAccTime;
    float m_fMaxTime;
    
    bool  m_bState;
};

