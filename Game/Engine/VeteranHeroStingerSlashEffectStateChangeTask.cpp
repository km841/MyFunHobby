#include "pch.h"
#include "VeteranHeroStingerSlashEffectStateChangeTask.h"
#include "VeteranHero.h"

VeteranHeroStingerSlashEffectStateChangeTask::VeteranHeroStingerSlashEffectStateChangeTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

VeteranHeroStingerSlashEffectStateChangeTask::~VeteranHeroStingerSlashEffectStateChangeTask()
{
}

BEHAVIOR_RESULT VeteranHeroStingerSlashEffectStateChangeTask::Run()
{
	weak_ptr<VeteranHero> pVeteranHero = static_pointer_cast<VeteranHero>(m_pGameObject.lock());
	pVeteranHero.lock()->CreateStingerSlashEffectAndAddedToScene();
	return BEHAVIOR_RESULT::SUCCESS;
}
