#pragma once
#include "Event.h"

class GameObject;

class ObjectAddedToSceneEvent :
    public Event
{
public:
    ObjectAddedToSceneEvent(shared_ptr<GameObject> pGameObject, SCENE_TYPE eSceneType);
    shared_ptr<GameObject> GetGameObject() { return std::move(m_pGameObject); }
    FORCEINLINE SCENE_TYPE GetSceneType() { return m_eSceneType; }

private:
    shared_ptr<GameObject> m_pGameObject;
    SCENE_TYPE m_eSceneType;
};

