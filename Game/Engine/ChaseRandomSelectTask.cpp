#include "pch.h"
#include "ChaseRandomSelectTask.h"
#include "Monster.h"

ChaseRandomSelectTask::ChaseRandomSelectTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT ChaseRandomSelectTask::Run()
{
	int32 iRandom = RANDOM(1, 2);
	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(m_pGameObject.lock());
	if (iRandom == 1)
	{
		pMonster.lock()->SetMonsterState(MONSTER_STATE::ATTACK_A_READY);
	}

	else if (iRandom == 2)
	{
		pMonster.lock()->SetMonsterState(MONSTER_STATE::ATTACK_B_READY);
	}

	return BEHAVIOR_RESULT::SUCCESS;
}
