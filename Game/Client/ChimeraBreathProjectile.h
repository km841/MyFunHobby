#pragma once
#include "MonsterProjectile.h"
class ChimeraBreathProjectile :
    public MonsterProjectile
{
public:
    ChimeraBreathProjectile();
    virtual ~ChimeraBreathProjectile();

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
    float m_fRotateZAcc;
    
};

