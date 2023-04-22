#include "pch.h"
#include "Physical.h"
#include "Engine.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "RigidBody.h"

Physical::Physical(ACTOR_TYPE eActorType, GEOMETRY_TYPE eGeometryType, Vec3 vGeometrySize, const MassProperties& massProperties)
	:Component(COMPONENT_TYPE::PHYSICAL)
	,m_eActorType(eActorType)
	,m_eGeometryType(eGeometryType)
	,m_pActor(nullptr)
	,m_vSize(vGeometrySize)
{
	CreatePhysicsProperties(massProperties);
	CreateGeometry(m_eGeometryType, m_vSize);
	CreateActor();
	CreateShape();
}

Physical::~Physical()
{
}

void Physical::Awake()
{
	assert(GetRigidBody());
	InitializeActor();
}

void Physical::CreateBoxGeometry(GEOMETRY_TYPE eGeometryType, const Vec3& vBoxSize)
{
	assert(GEOMETRY_TYPE::BOX == eGeometryType);
	assert(nullptr == m_pGeometries);
	m_pGeometries = make_shared<Geometries>(eGeometryType, vBoxSize);
}

void Physical::CreateCapsuleGeometry(GEOMETRY_TYPE eGeometryType, float fRadius, float fHalfHeight)
{
	assert(GEOMETRY_TYPE::CAPSULE == eGeometryType);
	assert(nullptr == m_pGeometries);
	m_pGeometries = make_shared<Geometries>(eGeometryType, fRadius, fHalfHeight);
}

void Physical::CreatePlaneGeometry(GEOMETRY_TYPE eGeometryType)
{
	assert(GEOMETRY_TYPE::PLANE == eGeometryType);
	assert(nullptr == m_pGeometries);
	m_pGeometries = make_shared<Geometries>(eGeometryType);
}

void Physical::CreateSphereGeometry(GEOMETRY_TYPE eGeometryType, float fRadius)
{
	assert(GEOMETRY_TYPE::SPHERE == eGeometryType);
	assert(nullptr == m_pGeometries);
	m_pGeometries = make_shared<Geometries>(eGeometryType, fRadius);
}

void Physical::CreatePhysicsProperties(const MassProperties& massProperties)
{
	m_pProperties = make_shared<PhysicsProperties>(massProperties);
}

void Physical::CreateGeometry(GEOMETRY_TYPE eGeometryType, const Vec3& vShapeSize)
{
	m_vSize = vShapeSize;

	switch (eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
		CreateBoxGeometry(eGeometryType, m_vSize);
		break;

	case GEOMETRY_TYPE::CAPSULE:
		CreateCapsuleGeometry(eGeometryType, m_vSize.x, m_vSize.y);
		break;

	case GEOMETRY_TYPE::SPHERE:
		CreateSphereGeometry(eGeometryType, m_vSize.x);
		break;

	case GEOMETRY_TYPE::PLANE:
		CreatePlaneGeometry(eGeometryType);
		break;
	}
}

void Physical::CreateShape()
{
	switch (m_eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
		m_pShape = PxRigidActorExt::createExclusiveShape(*m_pActor->is<PxRigidActor>(), m_pGeometries->boxGeom, *m_pProperties->GetMaterial());
		break;
	case GEOMETRY_TYPE::CAPSULE:
		m_pShape = PxRigidActorExt::createExclusiveShape(*m_pActor->is<PxRigidActor>(), m_pGeometries->capsuleGeom, *m_pProperties->GetMaterial());
		break;
	case GEOMETRY_TYPE::SPHERE:
		m_pShape = PxRigidActorExt::createExclusiveShape(*m_pActor->is<PxRigidActor>(), m_pGeometries->sphereGeom, *m_pProperties->GetMaterial());
		break;
	case GEOMETRY_TYPE::PLANE:
		m_pShape = PxRigidActorExt::createExclusiveShape(*m_pActor->is<PxRigidActor>(), m_pGeometries->planeGeom, *m_pProperties->GetMaterial());
		break;
	}
}


void Physical::CreateActor()
{
	switch (m_eActorType)
	{
	case ACTOR_TYPE::DYNAMIC:
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(PxVec3(0.f, 0.f, 0.f)));
		break;

	case ACTOR_TYPE::STATIC:
		m_pActor = PHYSICS->createRigidStatic(PxTransform(PxVec3(0.f, 0.f, 0.f)));
		break;

	case ACTOR_TYPE::KINEMATIC:
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(PxVec3(0.f, 0.f, 0.f)));
		m_pActor->is<PxRigidDynamic>()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
		break;

	case ACTOR_TYPE::CHARACTER:
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(PxVec3(0.f, 0.f, 0.f)));
		m_pActor->is<PxRigidDynamic>()->setRigidDynamicLockFlags(
			PxRigidDynamicLockFlag::eLOCK_LINEAR_Z |
			PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
			PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y);
		break;
	break;
	}
}

void Physical::InitializeActor()
{
	PxRigidActor* pActor = m_pActor->is<PxRigidActor>();
	pActor->userData = GetGameObject().get();

	PxVec3 vMyPos = Conv::Vec3ToPxVec3(GetTransform()->GetLocalPosition());
	pActor->setGlobalPose(PxTransform(vMyPos));

	switch (m_eActorType)
	{
	case ACTOR_TYPE::STATIC:
		break;
	case ACTOR_TYPE::DYNAMIC:
		GetRigidBody()->SetLinearDamping(0.5f);
		GetRigidBody()->SetLinearMaxVelocityForDynamic(1000.f);
		GetRigidBody()->SetAngularMaxVelocityForDynamic(500.f);
		break;
	case ACTOR_TYPE::KINEMATIC:
		m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		m_pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
		break;
	case ACTOR_TYPE::CHARACTER:
		break;
	}
	
}

void Physical::AddActorToPxScene()
{
	PX_SCENE->AddActor(m_pActor);
}

void Physical::RemoveActorToPxScene()
{
	PX_SCENE->RemoveActor(m_pActor);
}
