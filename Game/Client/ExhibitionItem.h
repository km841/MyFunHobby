#pragma once
#include "GameObject.h"
class HUD;
class ExhibitionItem :
    public GameObject
{
public:
    ExhibitionItem(ITEM_KIND eItemKind, int32 iPrice);
    virtual ~ExhibitionItem();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Destroy();

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject);

    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

public:
    FORCEINLINE int32 GetPrice() { return m_iPrice; }
    FORCEINLINE bool IsDestroy() { return m_bDestroyFlag; }

private:
    void CreateDetailHUDAndAddedToScene();

protected:
    bool m_bIsCollisionWithPlayer;
    bool m_bDestroyFlag;
    int32 m_iPrice;
    ITEM_KIND m_eItemKind;

    weak_ptr<GameObject> m_pDetailHUD;
};

