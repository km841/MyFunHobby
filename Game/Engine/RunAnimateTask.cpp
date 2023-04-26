#include "pch.h"
#include "RunAnimateTask.h"
#include "Animation.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Transform.h"


RunAnimateTask::RunAnimateTask(shared_ptr<GameObject> pGameObject, const wstring& szAnimationName, bool bLoop, uint32 iSection)
	: BehaviorTask(pGameObject)
	, m_szAnimationName(szAnimationName)
	, m_bLoop(bLoop)
	, m_iSection(iSection)
{
}

BEHAVIOR_RESULT RunAnimateTask::Run()
{
	if (m_pGameObject.lock()->GetAnimator())
	{

		if (m_szAnimationName != m_pGameObject.lock()->GetAnimator()->GetActiveAnimation()->GetName())
		{
			m_pGameObject.lock()->GetAnimator()->Play(m_szAnimationName, m_bLoop, m_iSection);
		}
	}

	return BEHAVIOR_RESULT::SUCCESS;
}
