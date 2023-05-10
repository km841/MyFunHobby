#pragma once
#include "GameObject.h"
class DecoObject :
    public GameObject
{
public:
    DecoObject();
    virtual ~DecoObject();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

