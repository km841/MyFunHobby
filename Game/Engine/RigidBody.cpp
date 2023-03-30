#include "pch.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Controller.h"
#include "Engine.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Physical.h"
#include "Timer.h"
#include "Engine.h"

RigidBody::RigidBody(bool bGravityApplied)
	: Component(COMPONENT_TYPE::RIGIDBODY)
	, m_bGravityApplied(bGravityApplied)
	, m_fMass(1.f)
{
	m_vGravityAccel = Vec3(0.f, -7.81f, 0.f);
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
		m_vVelocity += m_vGravityAccel;
}

void RigidBody::Move()
{

}


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