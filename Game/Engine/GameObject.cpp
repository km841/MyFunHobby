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
#include "AI.h"
#include "Scenes.h"

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

shared_ptr<AI> GameObject::GetAI()
{
	shared_ptr<Component> pComponent = GetFixedComponent(COMPONENT_TYPE::AI);
	return static_pointer_cast<AI>(pComponent);
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

CollisionInfo GameObject::IsCollisionSide()
{
	assert(GetPhysical());
	assert(GetCollider());

	Vec3 vMyPos = Conv::PxVec3ToVec3(GetTransform()->GetPxTransform().p);
	const Vec3& vMySize = GetPhysical()->GetGeometrySize();

	float fTolerance = 3.f;

	Vec3 vTopLeft = Vec3(vMyPos.x - (vMySize.x - fTolerance), vMyPos.y + (vMySize.y + fTolerance), vMyPos.z);
	Vec3 vTopRight = Vec3(vMyPos.x + (vMySize.x - fTolerance), vMyPos.y + (vMySize.y + fTolerance), vMyPos.z);

	Vec3 vBtmLeft = Vec3(vMyPos.x - (vMySize.x - fTolerance), vMyPos.y - (vMySize.y - fTolerance), vMyPos.z);
	Vec3 vBtmRight = Vec3(vMyPos.x + (vMySize.x - fTolerance), vMyPos.y - (vMySize.y - fTolerance), vMyPos.z);

	Vec3 vRightTop = Vec3(vMyPos.x + (vMySize.x + fTolerance), vMyPos.y + (vMySize.y - fTolerance), vMyPos.z);
	Vec3 vRightBtm = Vec3(vMyPos.x + (vMySize.x + fTolerance), vMyPos.y - (vMySize.y - fTolerance), vMyPos.z);

	Vec3 vLeftTop = Vec3(vMyPos.x - (vMySize.x - fTolerance), vMyPos.y + (vMySize.y - fTolerance), vMyPos.z);
	Vec3 vLeftBtm = Vec3(vMyPos.x - (vMySize.x - fTolerance), vMyPos.y - (vMySize.y - fTolerance), vMyPos.z);

	Vec3 vLeftDir = -VEC3_RIGHT_NORMAL;
	Vec3 vRightDir = VEC3_RIGHT_NORMAL;
	Vec3 vTopDir = VEC3_UP_NORMAL;
	Vec3 vBtmDir = -VEC3_UP_NORMAL;

	uint32 iCollisionFlags = 0;

	const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);

	for (const auto& pGameObject : vGameObjects)
	{
		bool bTopDirFromLeftTop = GetCollider()->Raycast(vTopLeft, vTopDir, pGameObject, 1.f);
		bool bTopDirFromRightTop = GetCollider()->Raycast(vTopRight, vTopDir, pGameObject, 1.f);

		if (bTopDirFromLeftTop || bTopDirFromRightTop)
		{
			float fTileCollisionPos = pGameObject->GetTransform()->GetWorldPosition().y - TILE_SIZE - fTolerance;
			return CollisionInfo(COLLISION_SIDE::TOP, fTileCollisionPos);
		}

		bool bBtmDirFromLeftBtm = GetCollider()->Raycast(vBtmLeft, vBtmDir, pGameObject, 1.f);
		bool bBtmDirFromRightBtm = GetCollider()->Raycast(vBtmRight, vBtmDir, pGameObject, 1.f);

		if (bBtmDirFromLeftBtm || bBtmDirFromRightBtm)
		{
			float fTileCollisionPos = pGameObject->GetTransform()->GetWorldPosition().y + TILE_SIZE + fTolerance;
			return CollisionInfo(COLLISION_SIDE::BOTTOM, fTileCollisionPos);
		}

		bool bLeftDirFromLeftTop = GetCollider()->Raycast(vLeftTop, vLeftDir, pGameObject, 1.f);
		bool bLeftDirFromLeftBtm = GetCollider()->Raycast(vLeftBtm, vLeftDir, pGameObject, 1.f);
		if (bLeftDirFromLeftTop || bLeftDirFromLeftBtm)
		{
			float fTileCollisionPos = pGameObject->GetTransform()->GetWorldPosition().x + TILE_SIZE + fTolerance;
			return CollisionInfo(COLLISION_SIDE::LEFT, fTileCollisionPos);
		}

		bool bRightDirFromRightTop = GetCollider()->Raycast(vRightTop, vRightDir, pGameObject, 1.f);
		bool bRightDirFromRightBtm = GetCollider()->Raycast(vRightBtm, vRightDir, pGameObject, 1.f);
		if (bRightDirFromRightTop || bRightDirFromRightBtm)
		{
			float fTileCollisionPos = pGameObject->GetTransform()->GetWorldPosition().x - TILE_SIZE - fTolerance;
			return CollisionInfo(COLLISION_SIDE::RIGHT, fTileCollisionPos);
		}
	}

	return CollisionInfo(COLLISION_SIDE::END, 0.f);;
}



