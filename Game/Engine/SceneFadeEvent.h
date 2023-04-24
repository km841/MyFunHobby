#pragma once
#include "Event.h"
class SceneFadeEvent :
    public Event
{
public:
    explicit SceneFadeEvent(SCENE_TYPE eSceneType, SCENE_FADE_EFFECT eSceneFadeEffect, float fEndTime);
    FORCEINLINE SCENE_TYPE GetSceneType() { return m_eSceneType; }
    FORCEINLINE SCENE_FADE_EFFECT GetFadeEffectType() { return m_eSceneFadeEffect; }
    FORCEINLINE float GetEndTime() { return m_fEndTime; }

private:
    SCENE_TYPE m_eSceneType;
    SCENE_FADE_EFFECT m_eSceneFadeEffect;
    float m_fEndTime;

};

