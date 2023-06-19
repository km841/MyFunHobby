#include "pch.h"
#include "VeteranHeroRandomStateTask.h"
#include "Monster.h"

VeteranHeroRandomStateTask::VeteranHeroRandomStateTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT VeteranHeroRandomStateTask::Run()
{
	int32 iRandom = RANDOM(1, 7);
	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(m_pGameObject.lock());
	if (iRandom == 1 || iRandom == 2)
	{
		pMonster.lock()->SetMonsterState(MONSTER_STATE::TRACE);
	}

	else if (iRandom == 3)
	{
		pMonster.lock()->SetMonsterState(MONSTER_STATE::ATTACK_C_READY);
	}

	else if (iRandom == 4)
	{
		pMonster.lock()->SetMonsterState(MONSTER_STATE::SKILL1_READY);
	}

	else
	{
		pMonster.lock()->SetMonsterState(MONSTER_STATE::FLEE);
	}

	return BEHAVIOR_RESULT::SUCCESS;
}
