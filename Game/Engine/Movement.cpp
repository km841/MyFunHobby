#include "pch.h"
#include "Movement.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Clock.h"
#include "Physical.h"
#include "Engine.h"
#include "Player.h"
#include "Collider.h"
#include "Scenes.h"
#include "Scene.h"

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

	if (LAYER_TYPE::PLAYER == GetGameObject()->GetLayerType())
	{
		if (PLAYER_STATE::ATTACK == GetPlayerStateEnum())
			return;

	}

	Move(vVelocity);
}


void Movement::Move(const Vec3& vVelocity)
{
	PxTransform transform = GetTransform()->GetPxTransform();
	transform.p += Conv::Vec3ToPxVec3(vVelocity * DELTA_TIME);

	if (ACTOR_TYPE::KINEMATIC == GetPhysical()->GetActorType())
		GetPhysical()->GetActor<PxRigidDynamic>()->setKinematicTarget(transform);
	else
		GetPhysical()->GetActor<PxRigidDynamic>()->setGlobalPose(transform);

	GetRigidBody()->SetVelocity(AXIS::X, 0.f);
}
