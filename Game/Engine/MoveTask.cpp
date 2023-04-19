#include "pch.h"
#include "MoveTask.h"
#include "Transform.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "Clock.h"

MoveTask::MoveTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_tDuration(3.f)
{
	m_tDuration.Start();
}

BEHAVIOR_RESULT MoveTask::Run()
{
	uint8 iDirection = static_cast<uint8>(m_pGameObject.lock()->GetDirection());
	if (m_tDuration.IsRunning())
	{
		m_tDuration.Update(DELTA_TIME);
	}

	if (m_tDuration.IsFinished())
	{
		m_pGameObject.lock()->SetDirection(static_cast<DIRECTION>((iDirection + 1) % 2));
		m_tDuration.Start();
	}

	CollisionInfo collisionInfo = m_pGameObject.lock()->IsCollisionSide();
	if (COLLISION_SIDE::RIGHT == collisionInfo.first && !iDirection)
	{
		m_pGameObject.lock()->SetDirection(static_cast<DIRECTION>((iDirection + 1) % 2));
	}
	if (COLLISION_SIDE::LEFT == collisionInfo.first && iDirection)
	{
		m_pGameObject.lock()->SetDirection(static_cast<DIRECTION>((iDirection + 1) % 2));
	}

	m_pGameObject.lock()->GetRigidBody()->SetVelocity(AXIS::X, iDirection ? -100.f : 100.f);

	return BEHAVIOR_RESULT::SUCCESS;
}
