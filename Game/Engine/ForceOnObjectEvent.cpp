#include "pch.h"
#include "ForceOnObjectEvent.h"

ForceOnObjectEvent::ForceOnObjectEvent(shared_ptr<GameObject> pGameObject, const PxVec3& vForce)
	: m_pGameObject(pGameObject)
	, m_vForce(vForce)
{
	m_eEventType = EVENT_TYPE::FORCE_ON_OBJECT_EVENT;
}
