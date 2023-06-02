#pragma once
#include "LocalEffect.h"
class JennysChainSickleSlashEffect :
    public LocalEffect
{
public:
    JennysChainSickleSlashEffect();
    virtual ~JennysChainSickleSlashEffect();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    DECLARE_POOL(JennysChainSickleSlashEffect);

};

