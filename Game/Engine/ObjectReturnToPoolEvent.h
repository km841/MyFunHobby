#pragma once
#include "Event.h"
class GameObject;
class ObjectReturnToPoolEvent :
    public Event
{
public:
    ObjectReturnToPoolEvent(shared_ptr<GameObject> pGameObject, SCENE_TYPE eSceneType);
    shared_ptr<GameObject> GetGameObject() { return std::move(m_pGameObject); }
    FORCEINLINE SCENE_TYPE GetSceneType() { return m_eSceneType; }

private:
    shared_ptr<GameObject> m_pGameObject;
    SCENE_TYPE m_eSceneType;
};

