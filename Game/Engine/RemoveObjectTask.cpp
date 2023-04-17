#include "pch.h"
#include "RemoveObjectTask.h"
#include "EventManager.h"
#include "Scene.h"
#include "Scenes.h"
#include "ObjectRemoveToSceneEvent.h"
#include "Monster.h"

RemoveObjectTask::RemoveObjectTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT RemoveObjectTask::Run()
{
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pGameObject.lock(), eSceneType));
	static_pointer_cast<Monster>(m_pGameObject.lock())->ActivateDeadEvent();
	m_pGameObject.lock()->Release();

	return BEHAVIOR_RESULT::SUCCESS;
}
