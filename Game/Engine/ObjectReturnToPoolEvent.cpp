#include "pch.h"
#include "ObjectReturnToPoolEvent.h"
#include "GameObject.h"

ObjectReturnToPoolEvent::ObjectReturnToPoolEvent(shared_ptr<GameObject> pGameObject, SCENE_TYPE eSceneType)
	: m_pGameObject(pGameObject)
	, m_eSceneType(eSceneType)
{
	m_eEventType = EVENT_TYPE::OBJECT_RETURN_TO_POOL;
}
