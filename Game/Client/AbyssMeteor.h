#pragma once
#include "PlayerProjectile.h"
class GlobalEffect;
class AbyssMeteor :
    public PlayerProjectile
{
public:
    AbyssMeteor();
    virtual ~AbyssMeteor();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    void CreateSmokeEffectAndAddedScene();
    void EnableAndInitSmokeEffect();

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    static shared_ptr<GlobalEffect> s_pSmokeEffect;

private:
    float m_fMaxDistance;
    float m_fImpulse;
};

