#pragma once
#include "GameObject.h"

class HUD :
    public GameObject
{
public:
    HUD();
    virtual ~HUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:


private:

};

