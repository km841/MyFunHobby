#include "pch.h"
#include "RandomDirectionTask.h"
#include "Player.h"
#include "Transform.h"

RandomDirectionTask::RandomDirectionTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT RandomDirectionTask::Run()
{
	m_pGameObject.lock()->SetDirection(RANDOM(0, 1) ? DIRECTION::LEFT : DIRECTION::RIGHT);
	return BEHAVIOR_RESULT::SUCCESS;
}
