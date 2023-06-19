#include "pch.h"
#include "VeteranHeroStingerEffectStateChangeTask.h"
#include "VeteranHero.h"

VeteranHeroStingerEffectStateChangeTask::VeteranHeroStingerEffectStateChangeTask(shared_ptr<GameObject> pGameObject, bool bState)
	: BehaviorTask(pGameObject)
	, m_bState(bState)
{
}

VeteranHeroStingerEffectStateChangeTask::~VeteranHeroStingerEffectStateChangeTask()
{
}

BEHAVIOR_RESULT VeteranHeroStingerEffectStateChangeTask::Run()
{
	weak_ptr<VeteranHero> pVeteranHero = static_pointer_cast<VeteranHero>(m_pGameObject.lock());
	pVeteranHero.lock()->SetStingerEffectState(m_bState);
	return BEHAVIOR_RESULT::SUCCESS;
}
