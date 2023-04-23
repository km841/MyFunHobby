#pragma once
#include "PlayerProjectile.h"
class GlobalEffect;
class HighWarlockBaseProjectile :
    public PlayerProjectile
{
public:
    HighWarlockBaseProjectile();
    virtual ~HighWarlockBaseProjectile();
    
public:
    virtual void Awake() override;
    virtual void Start() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void FinalUpdate() override;

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    DECLARE_POOL(HighWarlockBaseProjectile);

private:
    bool m_bDespawn;
};

