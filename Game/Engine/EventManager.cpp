#include "pch.h"
#include "EventManager.h"
#include "SceneChangeEvent.h"
#include "ObjectAddedToSceneEvent.h"
#include "PlayerChangeStateEvent.h"
#include "Scenes.h"
#include "StateMachine.h"
#include "ObjectRemoveToSceneEvent.h"
#include "ObjectReturnToPoolEvent.h"
#include "Physical.h"
#include "Engine.h"
#include "Physics.h"
#include "ForceOnObjectEvent.h"
#include "Transform.h"

void EventManager::AddEvent(unique_ptr<Event> pEvent)
{
	m_qEvents.push(std::move(pEvent));
}

void EventManager::ProcessEvents()
{
	while (!m_qEvents.empty())
	{
		unique_ptr<Event> pEvent = std::move(m_qEvents.front());
		m_qEvents.pop();

		switch (pEvent->GetEventType())
		{
		case EVENT_TYPE::SCENE_CHANGE:
			// 이 함수는 pEvent를 참조하긴 하지만 소유하지는 않는다
			ProcessSceneChangeEvent(static_cast<SceneChangeEvent*>(pEvent.get()));
			break;

		case EVENT_TYPE::OBJECT_ADDED_TO_SCENE:
			ProcessObjectAddedEvent(static_cast<ObjectAddedToSceneEvent*>(pEvent.get()));
			break;

		case EVENT_TYPE::OBJECT_REMOVE_TO_SCENE:
			ProcessObjectRemoveEvent(static_cast<ObjectRemoveToSceneEvent*>(pEvent.get()));
			break;

		case EVENT_TYPE::OBJECT_RETURN_TO_POOL:
			ProcessObjectReturnToPoolEvent(static_cast<ObjectReturnToPoolEvent*>(pEvent.get()));
			break;

		case EVENT_TYPE::PLAYER_CHANGE_STATE:
			ProcessPlayerChangeStateEvent(static_cast<PlayerChangeStateEvent*>(pEvent.get()));
			break;

		case EVENT_TYPE::FORCE_ON_OBJECT_EVENT:
			ProcessForceOnObjectEvent(static_cast<ForceOnObjectEvent*>(pEvent.get()));
			break;
		}
	}
}

void EventManager::ProcessSceneChangeEvent(SceneChangeEvent* pEvent)
{
	GET_SINGLE(Scenes)->ChangeScene(pEvent->GetSceneType());
}

void EventManager::ProcessObjectAddedEvent(ObjectAddedToSceneEvent* pEvent)
{
	const auto& pCurScene = GET_SINGLE(Scenes)->m_arrScenes[static_cast<uint8>(pEvent->GetSceneType())];
	pCurScene->AddGameObject(pEvent->GetGameObject());
	shared_ptr<GameObject> pGameObject = pEvent->GetGameObject();
}

void EventManager::ProcessObjectRemoveEvent(ObjectRemoveToSceneEvent* pEvent)
{
	const auto& pCurScene = GET_SINGLE(Scenes)->m_arrScenes[static_cast<uint8>(pEvent->GetSceneType())];
	shared_ptr<GameObject> pGameObject = pEvent->GetGameObject();
	pCurScene->RemoveGameObject(pGameObject);
	if (pGameObject->GetPhysical())
	{
		pGameObject->GetPhysical()->RemoveActorToPxScene();
	}
}

void EventManager::ProcessObjectReturnToPoolEvent(ObjectReturnToPoolEvent* pEvent)
{
	const auto& pCurScene = GET_SINGLE(Scenes)->m_arrScenes[static_cast<uint8>(pEvent->GetSceneType())];
	shared_ptr<GameObject> pGameObject = pEvent->GetGameObject();
	pCurScene->RemoveGameObject(pGameObject);
	if (pGameObject->GetPhysical())
	{
		pGameObject->GetPhysical()->RemoveActorToPxScene();
	}
	
	pGameObject->Release();
}

void EventManager::ProcessPlayerChangeStateEvent(PlayerChangeStateEvent* pEvent)
{
	shared_ptr<Player> pPlayer = pEvent->GetPlayer();
	pPlayer->ChangePlayerState(pEvent->GetNextPlayerState());
}

void EventManager::ProcessForceOnObjectEvent(ForceOnObjectEvent* pEvent)
{
	shared_ptr<GameObject> pGameObject = pEvent->GetGameObject();
	assert(pGameObject->GetPhysical());

	const PxVec3& vImpulse = pEvent->GetForce();
	PxRigidBodyExt::addForceAtPos(
		*pGameObject->GetPhysical()->GetActor<PxRigidDynamic>(),
		vImpulse,
		Conv::Vec3ToPxVec3(pGameObject->GetTransform()->GetPhysicalPosition()),
		PxForceMode::eIMPULSE
	);
}
