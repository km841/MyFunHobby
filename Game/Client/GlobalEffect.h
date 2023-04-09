#pragma once
#include "GameObject.h"
class GlobalEffect :
    public GameObject
{
public:
    GlobalEffect(float fEndTime = 0.f);
    virtual ~GlobalEffect();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    Timer& GetTimer() { return m_tDuration; }

private:
    Timer m_tDuration;
};

