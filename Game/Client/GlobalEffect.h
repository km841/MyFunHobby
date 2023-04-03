#pragma once
#include "GameObject.h"
class GlobalEffect :
    public GameObject
{
public:
    GlobalEffect();
    virtual ~GlobalEffect();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:

};

