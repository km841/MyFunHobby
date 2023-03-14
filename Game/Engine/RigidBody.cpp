#include "pch.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Controller.h"
#include "Engine.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Physical.h"

RigidBody::RigidBody(ACTOR_TYPE eActorType)
	: Component(COMPONENT_TYPE::RIGIDBODY)
	, m_eActorType(eActorType)
{

}

RigidBody::~RigidBody()
{
}

void RigidBody::Awake()
{

}

void RigidBody::FinalUpdate()
{
	// 계산결과를 가져온다.
	switch (m_eActorType)
	{
	case ACTOR_TYPE::DYNAMIC:
	{
		PxTransform transform = static_cast<PxRigidDynamic*>(GetPhysical()->GetActor())->getGlobalPose();
		GetTransform()->SetLocalPosition(Conv::PxVec3ToVec3(transform.p));
	}
		break;
	case ACTOR_TYPE::STATIC:
		break;
	case ACTOR_TYPE::KINEMATIC:
		break;
	case ACTOR_TYPE::CHARACTER:
		GetTransform()->SetLocalPosition(Conv::PxExtendedVec3ToVec3(GetPhysical()->GetController()->getPosition()));
		break;
	}
}
