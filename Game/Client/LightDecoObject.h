#pragma once
#include "DecoObject.h"
class LightDecoObject :
    public DecoObject
{
public:
    LightDecoObject();
    virtual ~LightDecoObject();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    void CreateLightAndAddedToScene();

private:

};

