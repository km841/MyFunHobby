#pragma once
#include "Event.h"
class GameObject;
class ForceOnObjectEvent :
    public Event
{
public:
    ForceOnObjectEvent(shared_ptr<GameObject> pGameObject, const PxVec3& vForce);

public:
    FORCEINLINE shared_ptr<GameObject> GetGameObject() { return std::move(m_pGameObject); }
    FORCEINLINE const PxVec3&          GetForce()      { return m_vForce; }

private:
    shared_ptr<GameObject> m_pGameObject;
    PxVec3 m_vForce;
};

