#pragma once
#include "MonoBehaviour.h"
class ChimeraVenomFallScript :
    public MonoBehaviour
{
public:
    ChimeraVenomFallScript();
    virtual ~ChimeraVenomFallScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateVenomFallAndAddedToScene();

private:
    bool m_bChecked;
};

