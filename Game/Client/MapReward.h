#pragma once
#include "GameObject.h"
class LocalEffect;
class MapReward :
    public GameObject
{
public:
    MapReward(GRADE eGrade);
    virtual ~MapReward();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    FORCEINLINE bool IsTaked() { return m_bTaked; }

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

protected:
    GRADE m_eGrade;
    bool m_bTaked;
    bool m_bIsCollisionWithPlayer;
    shared_ptr<LocalEffect> m_pHoveringKeyEffect;
};

