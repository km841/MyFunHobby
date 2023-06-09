#pragma once
#include "GameObject.h"
class KirionDashSlashEffect :
    public GameObject
{
public:
    KirionDashSlashEffect();
    virtual ~KirionDashSlashEffect();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    DECLARE_POOL(KirionDashSlashEffect);

    wstring m_szAnimName;
    Timer m_tStayTime;
    bool m_bStarted;
};

