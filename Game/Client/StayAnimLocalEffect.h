#pragma once
#include "GameObject.h"
class StayAnimLocalEffect :
    public GameObject
{
public:
    StayAnimLocalEffect();
    virtual ~StayAnimLocalEffect();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    DECLARE_POOL(StayAnimLocalEffect);

    wstring m_szAnimName;
    Timer m_tStayTime;
    bool m_bStarted;
};

