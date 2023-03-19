#include "pch.h"
#include "EventManager.h"
#include "SceneChangeEvent.h"
#include "ObjectAddedToSceneEvent.h"
#include "PlayerChangeStateEvent.h"
#include "Scenes.h"
#include "StateMachine.h"

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

		case EVENT_TYPE::PLAYER_CHANGE_STATE:
			ProcessPlayerChangeStateEvent(static_cast<PlayerChangeStateEvent*>(pEvent.get()));
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
}

void EventManager::ProcessPlayerChangeStateEvent(PlayerChangeStateEvent* pEvent)
{
	shared_ptr<Player> pPlayer = pEvent->GetPlayer();
	pPlayer->m_pStateMachine->ChangePlayerState(pEvent->GetNextPlayerState());
}
