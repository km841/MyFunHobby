#pragma once
#include "MonoBehaviour.h"
class ChimeraFallParticlesScript :
    public MonoBehaviour
{
public:
    ChimeraFallParticlesScript();
    virtual ~ChimeraFallParticlesScript();

public:
    virtual void LateUpdate() override;

private:
};

