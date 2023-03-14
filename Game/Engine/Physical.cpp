#include "pch.h"
#include "Physical.h"
#include "Engine.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"

Physical::Physical(ACTOR_TYPE eActorType, GEOMETRY_TYPE eGeometryType, Vec3 vGeometrySize, MassProperties massProperties)
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

	if (m_pActor)
	{
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
			pController->setHalfSideExtent(pController->getHalfSideExtent() * vScale.x);
			pController->setHalfHeight(pController->getHalfHeight() * vScale.y);
			pController->setHalfForwardExtent(pController->getHalfForwardExtent() * vScale.z);
		}

		else
		{
			switch (m_eGeometryType)
			{
			case GEOMETRY_TYPE::BOX:
			{
				m_pGeometries->boxGeom.halfExtents = Conv::Vec3ToPxVec3(m_vSize * vScale);
				ApplyShapeScale();
			}
				break;
			case GEOMETRY_TYPE::CAPSULE:
			{
				m_pGeometries->capsuleGeom.radius = m_vSize.x * vScale.x;
				m_pGeometries->capsuleGeom.radius = m_vSize.y * vScale.y;
				ApplyShapeScale();
			}
				break;
			}	
		}

		GetTransform()->ChangedFlagOff();
	}
}

void Physical::CreateBoxGeometry(GEOMETRY_TYPE eGeometryType, Vec3 vBoxSize)
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

void Physical::CreatePhysicsProperties(MassProperties massProperties)
{
	m_pProperties = make_shared<PhysicsProperties>(massProperties);
}

void Physical::CreateGeometry(GEOMETRY_TYPE eGeometryType, Vec3 vShapeSize)
{
	m_vSize = vShapeSize;
	m_vSize *= GetTransform()->GetLocalScale();

	switch (eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
		CreateBoxGeometry(eGeometryType, vShapeSize);
		break;
	case GEOMETRY_TYPE::CAPSULE:
		CreateCapsuleGeometry(eGeometryType, vShapeSize.x, vShapeSize.y);
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
		m_pShape = PHYSICS->createShape(m_pGeometries->boxGeom, *m_pProperties->GetMaterial());
		break;
	case GEOMETRY_TYPE::CAPSULE:
		m_pShape = PHYSICS->createShape(m_pGeometries->capsuleGeom, *m_pProperties->GetMaterial());
		break;
	case GEOMETRY_TYPE::PLANE:
		m_pShape = PHYSICS->createShape(m_pGeometries->planeGeom, *m_pProperties->GetMaterial());
		break;
	}
}

void Physical::CreateActor()
{
	switch (m_eActorType)
	{
	case ACTOR_TYPE::DYNAMIC:
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(Conv::Vec3ToPxVec3(GetTransform()->GetLocalPosition())));
		break;
	case ACTOR_TYPE::STATIC:
		m_pActor = PHYSICS->createRigidStatic(PxTransform(Conv::Vec3ToPxVec3(GetTransform()->GetLocalPosition())));
		break;
	case ACTOR_TYPE::KINEMATIC:
	{
		m_pActor = PHYSICS->createRigidDynamic(PxTransform(Conv::Vec3ToPxVec3(GetTransform()->GetLocalPosition())));
		PxRigidDynamic* pActor = m_pActor->is<PxRigidDynamic>();
		pActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
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

	if (m_pActor)
	{
		InitializeActor();
	}
}

void Physical::InitializeActor()
{
	CreateShape();

	// Collider에서 세팅
	PxFilterData filterData = {};
	filterData.word0 = 1 << 1;
	filterData.word1 = 1 << 0;
	m_pShape->setSimulationFilterData(filterData);

	switch (m_eActorType)
	{
	case ACTOR_TYPE::KINEMATIC:
	case ACTOR_TYPE::DYNAMIC:
	{
		PxRigidDynamic* pActor = m_pActor->is<PxRigidDynamic>();
		pActor->attachShape(*m_pShape);
		pActor->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z);
	}
		break;

	case ACTOR_TYPE::STATIC:
	{
		PxRigidStatic* pActor = m_pActor->is<PxRigidStatic>();
		pActor->attachShape(*m_pShape);
	}
		break;
	}

	PxRigidActor* pActor = m_pActor->is<PxRigidActor>();
	pActor->userData = g_pEngine->GetPhysics()->GetDispatcher()->GetSimulationCallback();
}

void Physical::CreateController()
{
	switch (m_eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		PxBoxControllerDesc desc;
		desc.setToDefault();
		// Half Size이므로 2를 곱해서 크기 복원
		desc.halfSideExtent = m_vSize.x;
		desc.halfHeight = m_vSize.y;
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
