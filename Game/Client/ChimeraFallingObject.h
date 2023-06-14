#pragma once
#include "GameObject.h"
class ChimeraFallingObject :
    public GameObject
{
public:
    ChimeraFallingObject();
    virtual ~ChimeraFallingObject();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject) override;

private:
    void CreateSmokeEffectAndAddedToScene();

private:
    bool m_bChecked;
    bool m_bTriggerFlag;
};

