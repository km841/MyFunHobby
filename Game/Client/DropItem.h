#pragma once
#include "GameObject.h"
class DropItem :
    public GameObject
{
public:
    DropItem(ITEM_KIND eItemKind);
    virtual ~DropItem();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    void CreateTouchEffectAddedToScene();

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    ITEM_KIND m_eItemKind;
    bool m_bIsCollisionWithPlayer;
};

