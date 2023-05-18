#include "pch.h"
#include "IsMonsterStateCondition.h"
#include "Monster.h"

IsMonsterStateCondition::IsMonsterStateCondition(shared_ptr<GameObject> pGameObject, MONSTER_STATE eMonsterState)
	: BehaviorCondition(pGameObject)
	, m_eMonsterState(eMonsterState)
{
}

IsMonsterStateCondition::~IsMonsterStateCondition()
{
}

BEHAVIOR_RESULT IsMonsterStateCondition::Run()
{
	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(m_pGameObject.lock());
	if (pMonster.lock()->GetMonsterState() == m_eMonsterState)
		return BEHAVIOR_RESULT::SUCCESS;
	else
		return BEHAVIOR_RESULT::FAILURE;
}
