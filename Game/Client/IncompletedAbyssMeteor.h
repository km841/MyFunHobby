#pragma once
#include "PlayerProjectile.h"
class IncompletedAbyssMeteor :
    public PlayerProjectile
{
public:
    IncompletedAbyssMeteor(const Vec3& vPos);
    virtual ~IncompletedAbyssMeteor();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    void CreateSmokeEffectAndAddedScene();

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    float m_fMaxDistance;
    float m_fImpulse;
    Vec3 m_vTargetPos;
};

