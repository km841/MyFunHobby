#include "pch.h"
#include "Physical.h"
#include "Engine.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"

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
	if (m_pActor)
	{
		InitializeActor();
	}
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

	if (ACTOR_TYPE::KINEMATIC == m_eActorType)
	{
		m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		m_pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	}
}


void Physical::CreateActor()
{
	switch (m_eActorType)
	{
	case ACTOR_TYPE::DYNAMIC:
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(PxVec3(0.f, 0.f, 0.f)));
		m_pActor->is<PxRigidDynamic>()->setLinearDamping(0.5f);
		//m_pActor->is<PxRigidDynamic>()->setAngularDamping(1.f);
		//m_pActor->is<PxRigidDynamic>()->setMass(2.f);
		//m_pActor->is<PxRigidDynamic>()->setMaxAngularVelocity(300.f);
		m_pActor->is<PxRigidDynamic>()->setMaxLinearVelocity(1000.f);
		break;
	case ACTOR_TYPE::STATIC:
		m_pActor = PHYSICS->createRigidStatic(PxTransform(PxVec3(0.f, 0.f, 0.f)));
		break;
	case ACTOR_TYPE::KINEMATIC:
	{
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(PxVec3(0.f, 0.f, 0.f)));
		m_pActor->is<PxRigidDynamic>()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	}
	break;
	}
}

void Physical::InitializeActor()
{
	PxRigidActor* pActor = m_pActor->is<PxRigidActor>();
	pActor->userData = GetGameObject().get();

	PxVec3 vMyPos = Conv::Vec3ToPxVec3(GetTransform()->GetLocalPosition());
	pActor->setGlobalPose(PxTransform(vMyPos));

	//pActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
}

void Physical::AddActorToPxScene()
{
	PX_SCENE->AddActor(m_pActor);
}

void Physical::RemoveActorToPxScene()
{
	PX_SCENE->GetScene()->removeActor(*m_pActor);
}
