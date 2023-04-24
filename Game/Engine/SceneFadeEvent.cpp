#include "pch.h"
#include "SceneFadeEvent.h"

SceneFadeEvent::SceneFadeEvent(SCENE_TYPE eSceneType, SCENE_FADE_EFFECT eSceneFadeEffect, float fEndTime)
	: m_eSceneType(eSceneType)
	, m_eSceneFadeEffect(eSceneFadeEffect)
	, m_fEndTime(fEndTime)
{
	m_eEventType = EVENT_TYPE::SCENE_FADE_EVENT;
}
