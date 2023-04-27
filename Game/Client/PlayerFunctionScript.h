#pragma once
#include "MonoBehaviour.h"
class PlayerFunctionScript :
    public MonoBehaviour
{
public:
    PlayerFunctionScript();
    virtual ~PlayerFunctionScript();

public:
    virtual void LateUpdate() override;
};

