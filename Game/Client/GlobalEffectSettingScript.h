#pragma once
#include "MonoBehaviour.h"
class GlobalEffectSettingScript :
    public MonoBehaviour
{
public:
    GlobalEffectSettingScript();
    virtual ~GlobalEffectSettingScript();

public:
    virtual void LateUpdate() override;
};

