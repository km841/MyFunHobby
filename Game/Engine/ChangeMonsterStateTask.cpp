#include "pch.h"
#include "ChangeMonsterStateTask.h"
#include "Monster.h"
#include "EventManager.h"
#include "MonsterChangeStateEvent.h"
#include "RigidBody.h"

ChangeMonsterStateTask::ChangeMonsterStateTask(shared_ptr<GameObject> pGameObject, MONSTER_STATE eMonsterState, bool bCondition)
	: BehaviorTask(pGameObject)
	, m_eMonsterState(eMonsterState)
	, m_bCondition(bCondition)
{
}

BEHAVIOR_RESULT ChangeMonsterStateTask::Run()
{
	m_pGameObject.lock()->GetRigidBody()->SetLinearVelocityForDynamic(AXIS::X, 0.f);
	static_pointer_cast<Monster>(m_pGameObject.lock())->SetMonsterState(m_eMonsterState);

	if (!m_bCondition)
		return BEHAVIOR_RESULT::FAILURE;
	else
		return BEHAVIOR_RESULT::SUCCESS;
}
