#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "DebugRenderer.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "MonoBehaviour.h"
#include "Controller.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Animator.h"
#include "Movement.h"
#include "Light.h"

GameObject::GameObject(LAYER_TYPE eLayerType)
	: Object(OBJECT_TYPE::GAMEOBJECT)
	, m_bDisable(false)
	, m_eDirection(DIRECTION::RIGHT)
	, m_eLayerType(eLayerType)
	, m_eLevelType(OBJECT_LEVEL_TYPE::OBJECT_LEVEL_1)
	
{
}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& pComponent : m_arrComponents)
	{
		if (pComponent)
			pComponent->Awake();
	}

	for (shared_ptr<MonoBehaviour>& pScript : m_vScripts)
	{
		if (pScript)
			pScript->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& pComponent : m_arrComponents)
	{
		if (pComponent)
			pComponent->Start();
	}

	for (shared_ptr<MonoBehaviour>& pScript : m_vScripts)
	{
		if (pScript)
			pScript->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& pComponent : m_arrComponents)
	{
		if (pComponent)
			pComponent->Update();
	}

	for (shared_ptr<MonoBehaviour>& pScript : m_vScripts)
	{
		if (pScript)
			pScript->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& pComponent : m_arrComponents)
	{
		if (pComponent)
			pComponent->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& pScript : m_vScripts)
	{
		if (pScript)
			pScript->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (shared_ptr<Component>& pComponent : m_arrComponents)
	{
		if (pComponent)
			pComponent->FinalUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(COMPONENT_TYPE eType)
{
	uint8 iIndex = static_cast<uint8>(eType);
	assert(FIXED_COMPONENT_COUNT > iIndex);
	return m_arrComponents[iIndex];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(pComponent);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::MESH_RENDERER);
	return static_pointer_cast<MeshRenderer>(pComponent);
}

shared_ptr<Collider> GameObject::GetCollider()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::COLLIDER);
	return static_pointer_cast<Collider>(pComponent);
}

shared_ptr<RigidBody> GameObject::GetRigidBody()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::RIGIDBODY);
	return static_pointer_cast<RigidBody>(pComponent);
}

shared_ptr<Physical> GameObject::GetPhysical()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::PHYSICAL);
	return static_pointer_cast<Physical>(pComponent);
}

shared_ptr<DebugRenderer> GameObject::GetDebugRenderer()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::DEBUG_RENDERER);
	return static_pointer_cast<DebugRenderer>(pComponent);
}

shared_ptr<Controller> GameObject::GetController()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::CONTROLLER);
	return static_pointer_cast<Controller>(pComponent);
}

shared_ptr<Camera> GameObject::GetCamera()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::CAMERA);
	return static_pointer_cast<Camera>(pComponent);
}

shared_ptr<Animator> GameObject::GetAnimator()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::ANIMATOR);
	return static_pointer_cast<Animator>(pComponent);
}

shared_ptr<Movement> GameObject::GetMovement()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::MOVEMENT);
	return static_pointer_cast<Movement>(pComponent);
}

shared_ptr<Light> GameObject::GetLight()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::LIGHT);
	return static_pointer_cast<Light>(pComponent);
}

void GameObject::AddComponent(shared_ptr<Component> pComponent)
{
	pComponent->SetGameObject(shared_from_this());

	uint8 iIndex = static_cast<uint8>(pComponent->GetType());

	if (FIXED_COMPONENT_COUNT > iIndex)
	{
		m_arrComponents[iIndex] = pComponent;
	}
	else
	{
		m_vScripts.push_back(dynamic_pointer_cast<MonoBehaviour>(pComponent));
	}
}

void GameObject::Release()
{
	for (int32 i = 0; i < FIXED_COMPONENT_COUNT; ++i)
	{
		if (m_arrComponents[i])
			m_arrComponents[i].reset();
	}
}
