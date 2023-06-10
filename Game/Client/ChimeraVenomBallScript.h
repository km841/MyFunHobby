#pragma once
#include "MonoBehaviour.h"
class ChimeraVenomBallScript :
    public MonoBehaviour
{
public:
    ChimeraVenomBallScript();
    virtual ~ChimeraVenomBallScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateVenomBallAndAddedToScene();

private:
    int32 m_iVenomBallCount;
    Timer m_tDuration;
};

