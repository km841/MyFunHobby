#pragma once
#include "GameObject.h"
class LocalEffect;
class HealthPotion :
    public GameObject
{
public:
    HealthPotion();
    virtual ~HealthPotion();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    void CreateHoveringKeyAndAddedToScene();

private:
    float m_fCount;
    bool m_bIsCollisionWithPlayer;
    shared_ptr<LocalEffect> m_pHoveringKeyEffect;
};

