#pragma once
#include "MonsterProjectile.h"
class AlchemistFlask :
    public MonsterProjectile
{
public:
    AlchemistFlask();
    virtual ~AlchemistFlask();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    bool m_bDespawnFlag;
    bool m_bChecked;
    bool m_bTimerOverFlag;
    Timer m_tLifeTime;

private:
    DECLARE_POOL(AlchemistFlask);
};

