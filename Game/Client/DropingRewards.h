#pragma once
#include "GameObject.h"
class DropingRewards :
    public GameObject
{
public:
    DropingRewards();
    virtual ~DropingRewards();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject);

private:
    bool m_bDestroy;
    Timer m_tDuration;

private:
    DECLARE_POOL(DropingRewards);
};

