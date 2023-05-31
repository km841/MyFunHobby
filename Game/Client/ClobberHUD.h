#pragma once
#include "HUD.h"
class ClobberHUD :
    public HUD
{
public:
    ClobberHUD();
    virtual ~ClobberHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

};

