#include "pch.h"
#include "ChangeChimeraRandomStateTask.h"
#include "Chimera.h"

ChangeChimeraRandomStateTask::ChangeChimeraRandomStateTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_bChecked(false)
{
}

BEHAVIOR_RESULT ChangeChimeraRandomStateTask::Run()
{
	weak_ptr<Chimera> pChimera = static_pointer_cast<Chimera>(m_pGameObject.lock());
	
	if (!m_bChecked)
	{
		if (pChimera.lock()->GetStatus()->GetHPRatio() < 0.5f)
		{
			pChimera.lock()->SetMonsterState(MONSTER_STATE::SKILL3_READY);
			m_bChecked = true;
		}
		else
		{
			int32 iRandom = RANDOM(0, 2);
			if (!iRandom)
			{
				pChimera.lock()->SetMonsterState(MONSTER_STATE::SKILL1_READY);
			}
			else
			{
				pChimera.lock()->SetMonsterState(MONSTER_STATE::SKILL2_READY);
			}
		}
	}
	else
	{
		int32 iRandom = RANDOM(0, 1);
		if (iRandom)
		{
			pChimera.lock()->SetMonsterState(MONSTER_STATE::SKILL1_READY);
		}
		else
		{
			pChimera.lock()->SetMonsterState(MONSTER_STATE::SKILL2_READY);
		}
	}


	return BEHAVIOR_RESULT::FAILURE;
}
