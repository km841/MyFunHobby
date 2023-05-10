#pragma once
#include "DecoObject.h"

class Ch3BeginTower :
    public DecoObject
{
public:
    Ch3BeginTower();
    virtual ~Ch3BeginTower();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    void CreateLightsAndAddedToScene();

private:
    std::vector<shared_ptr<DecoObject>> m_vLights;
};

