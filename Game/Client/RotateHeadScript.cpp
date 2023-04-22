#include "pch.h"
#include "RotateHeadScript.h"
#include "PlayerProjectile.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Clock.h"
#include "Physical.h"

RotateHeadScript::RotateHeadScript(weak_ptr<PlayerProjectile> pProjectile)
	: m_pProjectile(pProjectile)
	, m_fAngularSpeed(10.f)
	, m_fAccAngular(0.f)
{
}

RotateHeadScript::~RotateHeadScript()
{
}

void RotateHeadScript::LateUpdate()
{
	float fRotatedZ = m_pProjectile.lock()->GetTransform()->GetLocalRotation().z;
	fRotatedZ += m_fAngularSpeed * DELTA_TIME;
	
	
}
