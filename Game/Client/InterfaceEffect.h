#pragma once
#include "GameObject.h"
class InterfaceEffect :
    public GameObject
{
public:
    InterfaceEffect();
    virtual ~InterfaceEffect();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

