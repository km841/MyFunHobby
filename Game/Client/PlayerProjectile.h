#pragma once
#include "GameObject.h"
class PlayerProjectile :
    public GameObject
{
public:
    PlayerProjectile();
    virtual ~PlayerProjectile();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

};

