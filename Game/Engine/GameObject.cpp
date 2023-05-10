#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "DebugRenderer.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "MonoBehaviour.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Animator.h"
#include "Movement.h"
#include "Light.h"
#include "AI.h"
#include "Scenes.h"
#include "ParticleSystem.h"
#include "Tile.h"

GameObject::GameObject(LAYER_TYPE eLayerType)
	: Object(OBJECT_TYPE::GAMEOBJECT)
	, m_bDisable(false)
	, m_eDirection(DIRECTION::RIGHT)
	, m_eLayerType(eLayerType)
	, m_eLevelType(OBJECT_LEVEL_TYPE::OBJECT_LEVEL_1)
	, m_bCheckFrustum(true)
	, m_bAwake(false)
	
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

	m_bAwake = true;
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

shared_ptr<AI> GameObject::GetAI()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::AI);
	return static_pointer_cast<AI>(pComponent);
}

shared_ptr<ParticleSystem> GameObject::GetParticleSystem()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::PARTICLE_SYSTEM);
	return static_pointer_cast<ParticleSystem>(pComponent);
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
	m_vScripts.clear();
	ReturnToPool();
}

void GameObject::ReorganizePosition()
{
	assert(GetPhysical());
	assert(GetCollider());
	assert(GetRigidBody());

	const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);
	Vec3 vResult = {};
	for (const auto& pGameObject : vGameObjects)
	{
		if (TILE_TYPE::WALL != static_pointer_cast<Tile>(pGameObject)->GetTileType())
			continue;

		vResult = GetCollider()->ComputePenetration(pGameObject);
		if (vResult != Vec3::Zero)
		{
			if (vResult.x > 0.f)	  
				vResult.x += 1.f;
			else if (vResult.x < 0.f) 
				vResult.x -= 1.f;

			if (vResult.y < 0.f)
				GetRigidBody()->SetVelocity(AXIS::Y, 0.f);

			vResult.z = 0.f;
			GetTransform()->SetPhysicalPosition(GetTransform()->GetPhysicalPosition() + vResult);
			return;
		}
	}
}

void GameObject::ReorganizeVerticalPosition()
{
	assert(GetPhysical());
	assert(GetCollider());
	assert(GetRigidBody());

	const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);
	Vec3 vResult = {};
	for (const auto& pGameObject : vGameObjects)
	{
		if (TILE_TYPE::NONE == static_pointer_cast<Tile>(pGameObject)->GetTileType())
			continue;

		vResult = GetCollider()->ComputePenetration(pGameObject);
		if (vResult != Vec3::Zero)
		{
			vResult.x = 0.f;
			if (vResult.y < 0.f)
				GetRigidBody()->SetVelocity(AXIS::Y, 0.f);

			vResult.z = 0.f;
			GetTransform()->SetPhysicalPosition(GetTransform()->GetPhysicalPosition() + vResult);
			return;
		}
	}
}

bool GameObject::DoesTileExistInDirection(DIRECTION eDirection, float fDistance)
{
	Vec3 vGeomPos = GetTransform()->GetPhysicalPosition();
	const Vec3& vGeomSize = GetPhysical()->GetGeometrySize();

	const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);
	for (const auto& pGameObject : vGameObjects)
	{
		if (TILE_TYPE::WALL != static_pointer_cast<Tile>(pGameObject)->GetTileType())
			continue;

		if (DIRECTION::LEFT == eDirection)
		{
			Vec3 vLeft = Vec3(vGeomPos.x - TILE_HALF_SIZE - 1.f, vGeomPos.y, vGeomPos.z);
			if (GetCollider()->Raycast(vLeft, -VEC3_RIGHT_NORMAL, pGameObject, fDistance))
				return false;
		}
		else
		{
			Vec3 vRight = Vec3(vGeomPos.x + TILE_HALF_SIZE + 1.f, vGeomPos.y, vGeomPos.z);
			if (GetCollider()->Raycast(vRight, VEC3_RIGHT_NORMAL, pGameObject, fDistance))
				return false;
		}
	}

	return true;
}


