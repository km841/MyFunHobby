#pragma once
#include "PlayerProjectile.h"
class LittleBoneHead :
    public PlayerProjectile
{
public:
    LittleBoneHead();
    virtual ~LittleBoneHead();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject) override {}
    virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject) override {}

    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject) override;
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject) override;
};

