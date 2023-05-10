#pragma once
#include "GameObject.h"
class DropEssence :
    public GameObject
{
public:
    DropEssence(ESSENCE_KIND eEssenceKind);
    virtual ~DropEssence();

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
    ESSENCE_KIND m_eEssenceKind;
    bool m_bIsCollisionWithPlayer;
};

