#pragma once
#include "Event.h"
#include "Scene.h"

class SceneChangeEvent :
    public Event
{
public:
    SceneChangeEvent(SCENE_TYPE eSceneType);
    SCENE_TYPE GetSceneType() { return m_eSceneType; }

private:
    SCENE_TYPE m_eSceneType;
};

