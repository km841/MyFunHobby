#include "pch.h"
#include "IsHitCondition.h"
#include "Monster.h"
#include "RigidBody.h"

IsHitCondition::IsHitCondition(shared_ptr<GameObject> pGameObject)
	: BehaviorCondition(pGameObject)
{
}

IsHitCondition::~IsHitCondition()
{
}

BEHAVIOR_RESULT IsHitCondition::Run()
{
	if (static_pointer_cast<Monster>(m_pGameObject.lock())->IsHitFlag())
	{
		m_pGameObject.lock()->GetRigidBody()->SetVelocity(AXIS::X, 0.f);
		return BEHAVIOR_RESULT::SUCCESS;
	}
	else
	{
		return BEHAVIOR_RESULT::FAILURE;
	}
}
