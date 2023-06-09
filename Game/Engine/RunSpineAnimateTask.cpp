#include "pch.h"
#include "RunSpineAnimateTask.h"
#include "Chimera.h"

RunSpineAnimateTask::RunSpineAnimateTask(shared_ptr<GameObject> pGameObject, const string& szAnimationName, bool bLoop)
	: BehaviorTask(pGameObject)
	, m_szAnimationName(szAnimationName)
	, m_bLoop(bLoop)
{
}

BEHAVIOR_RESULT RunSpineAnimateTask::Run()
{
	weak_ptr<Chimera> pChimera = static_pointer_cast<Chimera>(m_pGameObject.lock());
	if (pChimera.lock()->GetCurAnimationName() == m_szAnimationName)
		return BEHAVIOR_RESULT::SUCCESS;

	pChimera.lock()->PlayAnimation(m_szAnimationName, m_bLoop);
	return BEHAVIOR_RESULT::SUCCESS;
}
