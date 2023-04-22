#include "pch.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Engine.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Physical.h"
#include "Clock.h"
#include "Engine.h"
#include "GameObject.h"

RigidBody::RigidBody(bool bGravityApplied)
	: Component(COMPONENT_TYPE::RIGIDBODY)
	, m_bGravityApplied(bGravityApplied)
{
	m_vGravityAccel = Vec3(0.f, -4500.f, 0.f);
	m_vVelocity = Vec3::Zero;
}

RigidBody::~RigidBody()
{
}

void RigidBody::Awake()
{
}

void RigidBody::FinalUpdate()
{
	if (m_bGravityApplied)
		m_vVelocity += m_vGravityAccel * DELTA_TIME;
}

// for kinematic actors
float RigidBody::GetVelocity(AXIS eAxis)
{
	switch (eAxis)
	{
	case AXIS::X:
		return m_vVelocity.x;
	case AXIS::Y:
		return m_vVelocity.y;
	case AXIS::Z:
		return m_vVelocity.z;
	}

	assert(nullptr);
	return PX_MAX_F32;
}

// for kinematic actors
void RigidBody::SetVelocity(AXIS eAxis, float fVelocity)
{
	switch (eAxis)
	{
	case AXIS::X:
		m_vVelocity.x = fVelocity;
		break;
	case AXIS::Y:
		m_vVelocity.y = fVelocity;
		break;
	}
}
// for kinematic actors
void RigidBody::AddVelocity(AXIS eAxis, float fVelocity)
{
	switch (eAxis)
	{
	case AXIS::X:
		m_vVelocity.x += fVelocity;
		break;
	case AXIS::Y:
		m_vVelocity.y += fVelocity;
		break;
	}
}

// for dynamic actors
void RigidBody::SetMassForDynamic(float fMass)
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setMass(fMass);
}
// for dynamic actors
void RigidBody::SetLinearVelocityForDynamic(const PxVec3& vLinearVelocity)
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setLinearVelocity(vLinearVelocity);
}

// for dynamic actors
void RigidBody::SetAngularVelocityForDynamic(const PxVec3& vAngularVelocity)
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setAngularVelocity(vAngularVelocity);
}

// for dynamic actors
void RigidBody::AddForceForDynamic(const PxVec3& vForce, PxForceMode::Enum eForceMode)
{
	assert(GetPhysical());
	assert(GetPhysical()->GetActor<PxRigidDynamic>());
	PxRigidBodyExt::addForceAtPos(
		*GetPhysical()->GetActor<PxRigidDynamic>(),
		vForce,
		Conv::Vec3ToPxVec3(GetTransform()->GetPhysicalPosition()),
		eForceMode);
}

// for dynamic actors
void RigidBody::SetLinearDamping(float fDamping)
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setLinearDamping(fDamping);
}

// for dynamic actors
void RigidBody::SetAngularDamping(float fDamping)
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setAngularDamping(fDamping);
}

// for dynamic actors
void RigidBody::SetLinearMaxVelocityForDynamic(float fMaxVelocity)
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setMaxLinearVelocity(fMaxVelocity);
}

// for dynamic actors
void RigidBody::SetAngularMaxVelocityForDynamic(float fMaxVelocity)
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setMaxAngularVelocity(fMaxVelocity);
}

// for dynamic actors
void RigidBody::ApplyGravityForDynamic()
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
}

// for dynamic actors
void RigidBody::RemoveGravityForDynamic()
{
	assert(GetPhysical());
	PxRigidDynamic* pDynamicActor = GetPhysical()->GetActor<PxRigidDynamic>();
	assert(pDynamicActor);
	pDynamicActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
}
