#pragma once
#include "GameObject.h"
class DropItem :
    public GameObject
{
public:
    DropItem(ITEM_KIND eItemKind, DROP_ITEM_INDEX eItemIndex);
    virtual ~DropItem();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Destroy();

public:
    void CreateTouchEffectAddedToScene();

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    void CreateDetailHUDAndAddedToScene();
    void DrawItemDetail();

private:
    ITEM_KIND m_eItemKind;
    bool m_bIsCollisionWithPlayer;
    bool m_bFixed;
    DROP_ITEM_INDEX m_eItemIndex;

    weak_ptr<GameObject> m_pDetailHUD;
    weak_ptr<GameObject> m_pVignetteHUD;
};

