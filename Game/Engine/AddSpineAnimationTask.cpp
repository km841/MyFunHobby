#include "pch.h"
#include "AddSpineAnimationTask.h"
#include "Chimera.h"

AddSpineAnimationTask::AddSpineAnimationTask(shared_ptr<GameObject> pGameObject, const string& szAnimationName, bool bLoop)
	: BehaviorTask(pGameObject)
	, m_szAnimationName(szAnimationName)
	, m_bLoop(bLoop)
{
}

BEHAVIOR_RESULT AddSpineAnimationTask::Run()
{
	weak_ptr<Chimera> pChimera = static_pointer_cast<Chimera>(m_pGameObject.lock());
	if (pChimera.lock()->GetCurAnimationName() == m_szAnimationName)
		return BEHAVIOR_RESULT::SUCCESS;

	pChimera.lock()->AddAnimation(m_szAnimationName, 0.f, m_bLoop);
	return BEHAVIOR_RESULT::SUCCESS;
}
