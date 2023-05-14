#pragma once
#include "DecoObject.h"
class LightObject :
    public GameObject
{
public:
    LightObject();
    virtual ~LightObject();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    void CreateLightAndAddedToScene();

private:

};

