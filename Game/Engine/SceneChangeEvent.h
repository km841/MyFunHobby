#pragma once
#include "Event.h"
#include "Scene.h"

class SceneChangeEvent :
    public Event
{
public:
    explicit SceneChangeEvent(SCENE_TYPE eSceneType);
    FORCEINLINE SCENE_TYPE GetSceneType() { return m_eSceneType; }

private:
    SCENE_TYPE m_eSceneType;
};

