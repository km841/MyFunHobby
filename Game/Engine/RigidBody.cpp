#include "pch.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Controller.h"
#include "Engine.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Physical.h"
#include "Timer.h"

RigidBody::RigidBody(bool bGravityApplied)
	: Component(COMPONENT_TYPE::RIGIDBODY)
	, m_bGravityApplied(bGravityApplied)
	, m_fMass(1.f)
{
	m_vGravityAccel = Vec3(0.f, -9.81f * 100.f, 0.f);
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

	Move();
}

void RigidBody::Move()
{
	PxTransform transform = GetTransform()->GetPxTransform();
	transform.p += Conv::Vec3ToPxVec3(m_vVelocity) * DELTA_TIME;
	GetPhysical()->GetActor()->is<PxRigidDynamic>()->setKinematicTarget(transform);
}

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