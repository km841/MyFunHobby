#include "pch.h"
#include "ObjectAddedToSceneEvent.h"

ObjectAddedToSceneEvent::ObjectAddedToSceneEvent(shared_ptr<GameObject> pGameObject, SCENE_TYPE eSceneType)
	:m_pGameObject(pGameObject)
	,m_eSceneType(eSceneType)
{
	m_eEventType = EVENT_TYPE::OBJECT_ADDED_TO_SCENE;
}
