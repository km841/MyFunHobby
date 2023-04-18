#include "pch.h"
#include "RemoveObjectTask.h"
#include "EventManager.h"
#include "Scene.h"
#include "Scenes.h"
#include "ObjectReturnToPoolEvent.h"
#include "Monster.h"

RemoveObjectTask::RemoveObjectTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

BEHAVIOR_RESULT RemoveObjectTask::Run()
{
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(m_pGameObject.lock(), eSceneType));

	return BEHAVIOR_RESULT::SUCCESS;
}
