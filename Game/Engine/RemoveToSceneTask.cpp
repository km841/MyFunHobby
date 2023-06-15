#include "pch.h"
#include "RemoveToSceneTask.h"
#include "EventManager.h"
#include "Scene.h"
#include "Scenes.h"
#include "ObjectRemoveToSceneEvent.h"

RemoveToSceneTask::RemoveToSceneTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT RemoveToSceneTask::Run()
{
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pGameObject.lock(), eSceneType));

	return BEHAVIOR_RESULT::SUCCESS;
}
