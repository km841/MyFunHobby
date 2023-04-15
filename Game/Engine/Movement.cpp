#include "pch.h"
#include "Movement.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Clock.h"
#include "Physical.h"
#include "Engine.h"
#include "Player.h"
#include "Collider.h"
#include "Scenes.h"
#include "Scene.h"

Movement::Movement()
	: Component(COMPONENT_TYPE::MOVEMENT)
{
}

Movement::~Movement()
{
}

void Movement::Awake()
{
}

void Movement::FinalUpdate()
{
	Vec3 vVelocity = GetRigidBody()->GetVelocity();

	if (LAYER_TYPE::PLAYER == GetGameObject()->GetLayerType())
	{
		if (PLAYER_STATE::ATTACK == GetPlayerStateEnum())
			return;

		if (PLAYER_STATE::SKILL == GetPlayerStateEnum())
			return;
	}

	if (GetPhysical())
		vVelocity = RegulateVelocity(vVelocity);

	Move(vVelocity);
}

const Vec3& Movement::RegulateVelocity(Vec3& vVelocity)
{
	//Vec3 vMyPos = Conv::PxVec3ToVec3(m_pGameObject.lock()->GetTransform()->GetPxTransform().p);
	//const Vec3& vMySize = m_pGameObject.lock()->GetPhysical()->GetGeometrySize();

	//Vec3 vLeftTop = Vec3(vMyPos.x - vMySize.x, vMyPos.y + vMySize.y, vMyPos.z);
	//Vec3 vLeftBtm = Vec3(vMyPos.x - vMySize.x, vMyPos.y - vMySize.y, vMyPos.z);
	//Vec3 vRightTop = Vec3(vMyPos.x + vMySize.x, vMyPos.y + vMySize.y, vMyPos.z);
	//Vec3 vRightBtm = Vec3(vMyPos.x + vMySize.x, vMyPos.y - vMySize.y, vMyPos.z);

	//Vec3 vLeftDir = -VEC3_RIGHT_NORMAL;
	//Vec3 vRightDir = VEC3_RIGHT_NORMAL;
	//Vec3 vTopDir = VEC3_UP_NORMAL;
	//Vec3 vBtmDir = -VEC3_UP_NORMAL;

	//float fRestitution = 200.f;
	//const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);
	//for (const auto& pGameObject : vGameObjects)
	//{
	//	bool bTopDirFromLeftTop = m_pGameObject.lock()->GetCollider()->Raycast(vLeftTop, vTopDir, pGameObject, 0.1f);
	//	bool bTopDirFromRightTop = m_pGameObject.lock()->GetCollider()->Raycast(vRightTop, vTopDir, pGameObject, 0.1f);
	//	bool bBtmDirFromLeftBtm = m_pGameObject.lock()->GetCollider()->Raycast(vLeftBtm, vBtmDir, pGameObject, 0.1f);
	//	bool bBtmDirFromRightBtm = m_pGameObject.lock()->GetCollider()->Raycast(vRightBtm, vBtmDir, pGameObject, 0.1f);
	//	bool bLeftDirFromLeftTop = m_pGameObject.lock()->GetCollider()->Raycast(vLeftTop, vLeftDir, pGameObject, 0.1f);
	//	bool bLeftDirFromLeftBtm = m_pGameObject.lock()->GetCollider()->Raycast(vLeftBtm, vLeftDir, pGameObject, 0.1f);
	//	bool bRightDirFromRightTop = m_pGameObject.lock()->GetCollider()->Raycast(vRightTop, vRightDir, pGameObject, 0.1f);
	//	bool bRightDirFromRightBtm = m_pGameObject.lock()->GetCollider()->Raycast(vRightBtm, vRightDir, pGameObject, 0.1f);

	//	if (bTopDirFromLeftTop || bTopDirFromRightTop)
	//		vVelocity.y = -fRestitution;
	//	
	//	else if (bBtmDirFromLeftBtm || bBtmDirFromRightBtm)
	//		vVelocity.y = fRestitution;
	//	
	//	if (bLeftDirFromLeftTop || bLeftDirFromLeftBtm)
	//		vVelocity.x = 0.f;
	//	
	//	else if (bRightDirFromRightTop || bRightDirFromRightBtm)
	//		vVelocity.x = 0.f;
	//}

	return vVelocity;
}

void Movement::Move(const Vec3& vVelocity)
{
	PxTransform transform = GetTransform()->GetPxTransform();
	transform.p += Conv::Vec3ToPxVec3(vVelocity * DELTA_TIME);

	if (ACTOR_TYPE::KINEMATIC == GetPhysical()->GetActorType())
		GetPhysical()->GetActor<PxRigidDynamic>()->setKinematicTarget(transform);

	
}
