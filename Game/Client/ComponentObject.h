#pragma once
#include "GameObject.h"
class ComponentObject :
    public GameObject
{
public:
    ComponentObject();
    virtual ~ComponentObject();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

