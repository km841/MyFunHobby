#pragma once
#include "MonoBehaviour.h"
class VeteranHeroLandingScript :
    public MonoBehaviour
{
public:
    VeteranHeroLandingScript();
    virtual ~VeteranHeroLandingScript();

public:
    virtual void LateUpdate() override;

private:
    bool m_bLandingReadyCompleteFlag;
    bool m_bLandingCompleteFlag;

    bool m_bLandingThrowingFlag;
};

