#pragma once
#include "GameObject.h"
class MonsterProjectile :
    public GameObject
{
public:
    MonsterProjectile();
    virtual ~MonsterProjectile();

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

