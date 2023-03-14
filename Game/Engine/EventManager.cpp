#include "pch.h"
#include "EventManager.h"
#include "SceneChangeEvent.h"
#include "Scenes.h"

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
			// �� �Լ��� pEvent�� �����ϱ� ������ ���������� �ʴ´�
			ProcessSceneChangeEvent(static_cast<SceneChangeEvent*>(pEvent.get()));
			break;
		}
	}
}

void EventManager::ProcessSceneChangeEvent(SceneChangeEvent* pEvent)
{
	GET_SINGLE(Scenes)->ChangeScene(pEvent->GetSceneType());
}
