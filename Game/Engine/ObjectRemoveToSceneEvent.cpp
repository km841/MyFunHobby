#include "pch.h"
#include "ObjectRemoveToSceneEvent.h"

ObjectRemoveToSceneEvent::ObjectRemoveToSceneEvent(shared_ptr<GameObject> pGameObject, SCENE_TYPE eSceneType)
	: m_pGameObject(pGameObject)
	, m_eSceneType(eSceneType)
{
	m_eEventType = EVENT_TYPE::OBJECT_REMOVE_TO_SCENE;
}
