#pragma once
#include "GameObject.h"
class ChimeraRoar :
    public GameObject
{
public:
    ChimeraRoar();
    virtual ~ChimeraRoar();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    Timer m_tDuration;
};

