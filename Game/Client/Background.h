#pragma once
#include "GameObject.h"
class Background :
    public GameObject
{
public:
    Background();
    virtual ~Background();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

