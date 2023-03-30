#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "DebugRenderer.h"
#include "MeshRenderer.h"
#include "Controller.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Camera.h"
#include "Animator.h"
#include "Player.h"
#include "Collider.h"
#include "Movement.h"

Component::Component(COMPONENT_TYPE eType)
    : Object(OBJECT_TYPE::COMPONENT)
    , m_eType(eType)
{
}

Component::~Component()
{
}

shared_ptr<GameObject> Component::GetGameObject()
{
    return m_pGameObject.lock();
}

shared_ptr<Transform> Component::GetTransform()
{
    return m_pGameObject.lock()->GetTransform();
}

shared_ptr<DebugRenderer> Component::GetDebugRenderer()
{
    return m_pGameObject.lock()->GetDebugRenderer();
}

shared_ptr<MeshRenderer> Component::GetMeshRenderer()
{
    return m_pGameObject.lock()->GetMeshRenderer();
}

shared_ptr<Controller> Component::GetController()
{
    return m_pGameObject.lock()->GetController();
}

shared_ptr<RigidBody> Component::GetRigidBody()
{
    return m_pGameObject.lock()->GetRigidBody();
}

shared_ptr<Physical> Component::GetPhysical()
{
    return m_pGameObject.lock()->GetPhysical();
}

shared_ptr<Camera> Component::GetCamera()
{
    return m_pGameObject.lock()->GetCamera();
}

shared_ptr<Animator> Component::GetAnimator()
{
    return m_pGameObject.lock()->GetAnimator();
}

shared_ptr<Collider> Component::GetCollider()
{
    return m_pGameObject.lock()->GetCollider();
}

shared_ptr<Movement> Component::GetMovement()
{
    return m_pGameObject.lock()->GetMovement();
}

PLAYER_STATE Component::GetPlayerStateEnum()
{
    return static_pointer_cast<Player>(m_pGameObject.lock())->GetPlayerStateEnum();
}