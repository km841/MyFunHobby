#pragma once
#include "MonoBehaviour.h"
class ChimeraBreathScript :
    public MonoBehaviour
{
public:
    ChimeraBreathScript();
    virtual ~ChimeraBreathScript();

public:
    virtual void LateUpdate() override;
};

