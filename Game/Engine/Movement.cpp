#include "pch.h"
#include "Movement.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Clock.h"
#include "Physical.h"
#include "Engine.h"

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
	if (Vec3::Zero == vVelocity)
		return;

	if (PLAYER_STATE::ATTACK_A == GetPlayerStateEnum() || 
		PLAYER_STATE::ATTACK_B == GetPlayerStateEnum())
	{
		return;
	}

	Move(vVelocity);
}

void Movement::Move(const Vec3& vVelocity)
{
	PxTransform transform = GetTransform()->GetPxTransform();
	transform.p += Conv::Vec3ToPxVec3(vVelocity * DELTA_TIME);
	GetPhysical()->GetActor()->is<PxRigidDynamic>()->setKinematicTarget(transform);
}
