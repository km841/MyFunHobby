#include "pch.h"
#include "ChangeMonsterStateTask.h"
#include "Monster.h"
#include "EventManager.h"
#include "MonsterChangeStateEvent.h"
#include "RigidBody.h"

ChangeMonsterStateTask::ChangeMonsterStateTask(shared_ptr<GameObject> pGameObject, MONSTER_STATE eMonsterState)
	: BehaviorTask(pGameObject)
	, m_eMonsterState(eMonsterState)
{
}

BEHAVIOR_RESULT ChangeMonsterStateTask::Run()
{
	m_pGameObject.lock()->GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
	GET_SINGLE(EventManager)->AddEvent(make_unique<MonsterChangeStateEvent>(static_pointer_cast<Monster>(m_pGameObject.lock()), m_eMonsterState));
	return BEHAVIOR_RESULT::FAILURE;
}
