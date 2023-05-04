#pragma once
#include "EventObject.h"
class DungeonGate :
    public EventObject
{
public:
    DungeonGate();
    virtual ~DungeonGate();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:

};

