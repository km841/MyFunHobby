#pragma once
#include "GameObject.h"
class Skul;
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
    virtual void Destroy();
public:
    void CreateTouchEffectAddedToScene();
    static wstring GetSkulImage(SKUL_KIND eSkulKind);

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    void DrawItemDetail();
    void CreateDetailHUDAndAddedToScene();
    void CreateDropSkulAndAddedToScene(shared_ptr<Skul> pSkul);

private:
    SKUL_KIND m_eSkulKind;
    bool m_bIsCollisionWithPlayer;
    bool m_bFixed;

    weak_ptr<GameObject> m_pDetailHUD;
    weak_ptr<GameObject> m_pVignetteHUD;
};

