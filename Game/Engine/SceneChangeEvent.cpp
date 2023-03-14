#include "pch.h"
#include "SceneChangeEvent.h"

SceneChangeEvent::SceneChangeEvent(SCENE_TYPE eSceneType)
	:m_eSceneType(eSceneType)
{
	m_eEventType = EVENT_TYPE::SCENE_CHANGE;
}

