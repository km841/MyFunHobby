#include "pch.h"
#include "FlipDirectionTask.h"

FlipDirectionTask::FlipDirectionTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT FlipDirectionTask::Run()
{
	uint8 eDirection = static_cast<uint8>(m_pGameObject.lock()->GetDirection());
	m_pGameObject.lock()->SetDirection(static_cast<DIRECTION>((eDirection + 1) % 2));
	return BEHAVIOR_RESULT::SUCCESS;
}
