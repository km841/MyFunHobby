#pragma once
#include "EventObject.h"
class Player;
class SceneChangeEventObject :
    public EventObject
{
public:
    SceneChangeEventObject(shared_ptr<Player> pPlayer);
    virtual ~SceneChangeEventObject();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);

private:
    weak_ptr<Player> m_pPlayer;
};

