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
	,m_pController(nullptr)
	,m_vSize(vGeometrySize)
{
	CreatePhysicsProperties(massProperties);
}

Physical::~Physical()
{
}

void Physical::Awake()
{
	CreateGeometry(m_eGeometryType, m_vSize);
	CreateActor();
	CreateShape();

	if (m_pActor)
	{
		InitializeActor();
		AddActor(m_pActor);
	}
}

void Physical::Update()
{
	if (GetTransform()->IsChangedFlag())
	{
		Vec3 vScale = GetTransform()->GetLocalScale();

		if (ACTOR_TYPE::CHARACTER == m_eActorType)
		{
			PxBoxController* pController = static_cast<PxBoxController*>(m_pController);
			pController->setHalfSideExtent(pController->getHalfSideExtent());
			pController->setHalfHeight(pController->getHalfHeight());
			pController->setHalfForwardExtent(pController->getHalfForwardExtent());
		}

		else
		{
			switch (m_eGeometryType)
			{
			case GEOMETRY_TYPE::BOX:
			{
				m_pGeometries->boxGeom.halfExtents = Conv::Vec3ToPxVec3(m_vSize);
				//ApplyShapeScale();
			}
				break;
			case GEOMETRY_TYPE::CAPSULE:
			{
				m_pGeometries->capsuleGeom.radius = m_vSize.x;
				m_pGeometries->capsuleGeom.halfHeight = m_vSize.y;
				//ApplyShapeScale();
			}
				break;
			}	
		}

		GetTransform()->ChangedFlagOff();
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
	case GEOMETRY_TYPE::PLANE:
		m_pShape = PxRigidActorExt::createExclusiveShape(*m_pActor->is<PxRigidActor>(), m_pGeometries->planeGeom, *m_pProperties->GetMaterial());
		break;
	}

	if (ACTOR_TYPE::KINEMATIC == m_eActorType)
	{
		m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		m_pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	}

	if (ACTOR_TYPE::NO_COLLISION_DYN == m_eActorType)
	{
		//m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		//m_pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
		//m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
	}
}


void Physical::CreateActor()
{
	switch (m_eActorType)
	{
	case ACTOR_TYPE::NO_COLLISION_DYN:
	case ACTOR_TYPE::DYNAMIC:
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(Conv::Vec3ToPxVec3(GetTransform()->GetLocalPosition())));
		break;
	case ACTOR_TYPE::STATIC:
		m_pActor = PHYSICS->createRigidStatic(PxTransform(Conv::Vec3ToPxVec3(GetTransform()->GetLocalPosition())));
		break;
	case ACTOR_TYPE::KINEMATIC:
	{
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(Conv::Vec3ToPxVec3(GetTransform()->GetLocalPosition())));
		m_pActor->is<PxRigidDynamic>()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	}
	break;

	case ACTOR_TYPE::CHARACTER:
	{
		CreateController();
		if (m_pController)
		{
			//m_pController->setUserData();
		}
	}
	break;
	}
}

void Physical::InitializeActor()
{
	switch (m_eActorType)
	{
	case ACTOR_TYPE::KINEMATIC:
	case ACTOR_TYPE::NO_COLLISION_DYN:
	case ACTOR_TYPE::DYNAMIC:
	{
		PxRigidDynamic* pActor = m_pActor->is<PxRigidDynamic>();

		pActor->setRigidDynamicLockFlags(
			PxRigidDynamicLockFlag::eLOCK_LINEAR_Z  | 
			PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | 
			PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y);
		//pActor->setAngularDamping(PX_MAX_F32);
	}
		break;

	case ACTOR_TYPE::STATIC:
	{
		// TODO
	}
		break;
	}

	PxRigidActor* pActor = m_pActor->is<PxRigidActor>();
	pActor->userData = GetGameObject().get();
	//pActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
}

void Physical::CreateController()
{
	
	switch (m_eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		PxBoxControllerDesc desc;
		desc.setToDefault();
		desc.halfSideExtent = m_vSize.x * 1.25f;
		desc.halfHeight = m_vSize.y * 1.25f;
		desc.halfForwardExtent = m_vSize.z;
		desc.material = m_pProperties->GetMaterial();
		m_pController = static_cast<PxBoxController*>(g_pEngine->GetPhysics()->GetEnvironment()->GetControllerManager()->createController(desc));
	}
		break;
	case GEOMETRY_TYPE::CAPSULE:
	{
		PxCapsuleControllerDesc desc;
		desc.setToDefault();
		desc.radius = m_vSize.x;
		desc.height = m_vSize.y;
		desc.material = m_pProperties->GetMaterial();
		m_pController = static_cast<PxCapsuleController*>(g_pEngine->GetPhysics()->GetEnvironment()->GetControllerManager()->createController(desc));
	}
		break;
	}

	m_pController->setPosition(Conv::Vec3ToPxExtendedVec3(GetTransform()->GetLocalPosition()));
	PxTransform transform = m_pController->getActor()->getGlobalPose();
	transform.q.z = 0.f;
	m_pController->getActor()->is<PxRigidDynamic>()->setGlobalPose(transform);	
}

void Physical::AddActor(PxActor* pActor)
{
	g_pEngine->GetPhysics()->GetEnvironment()->GetPhysScene()->AddActor(pActor);
}

void Physical::ApplyShapeScale()
{
	switch (m_eActorType)
	{
	case ACTOR_TYPE::STATIC:
	{
		PxRigidStatic* pActor = m_pActor->is<PxRigidStatic>();
		pActor->detachShape(*m_pShape);
		m_pShape->release();

		CreateShape();
		pActor->attachShape(*m_pShape);
	}
	break;
	case ACTOR_TYPE::DYNAMIC:
	case ACTOR_TYPE::NO_COLLISION_DYN:
	case ACTOR_TYPE::KINEMATIC:
	{
		PxRigidDynamic* pActor = m_pActor->is<PxRigidDynamic>();
		pActor->detachShape(*m_pShape);
		m_pShape->release();

		CreateShape();
		pActor->attachShape(*m_pShape);
	}
	break;
	}	
}
