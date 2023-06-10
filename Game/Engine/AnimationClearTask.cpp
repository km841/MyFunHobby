#include "pch.h"
#include "AnimationClearTask.h"
#include "Chimera.h"

AnimationClearTask::AnimationClearTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT AnimationClearTask::Run()
{
	static_pointer_cast<Chimera>(m_pGameObject.lock())->ClearAnimation();
	return BEHAVIOR_RESULT::SUCCESS;
}
