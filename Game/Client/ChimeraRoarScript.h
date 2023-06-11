#pragma once
#include "MonoBehaviour.h"
class ChimeraRoarScript :
    public MonoBehaviour
{
public:
    ChimeraRoarScript();
    virtual ~ChimeraRoarScript();

public:
    virtual void LateUpdate() override;
};

