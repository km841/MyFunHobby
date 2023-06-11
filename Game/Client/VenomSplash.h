#pragma once
#include "GameObject.h"
class VenomSplash :
    public GameObject
{
public:
    VenomSplash();
    virtual ~VenomSplash();

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
    bool m_bCollisionFlag;
    bool m_bChecked;

    bool m_bIntroFinishedFlag;
    bool m_bOutroFinishedFlag;

    Timer m_tLoopTimer;
};

