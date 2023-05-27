#pragma once
#include "GameObject.h"
class DropSkul :
    public GameObject
{
public:
    DropSkul(SKUL_KIND eSkulKind);
    virtual ~DropSkul();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    void CreateTouchEffectAddedToScene();

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    SKUL_KIND m_eSkulKind;
    bool m_bIsCollisionWithPlayer;
};

