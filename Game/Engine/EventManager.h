#pragma once
#include "Event.h"
class SceneChangeEvent;
class ObjectAddedToSceneEvent;
class PlayerChangeStateEvent;
class MonsterChangeStateEvent;
class ObjectRemoveToSceneEvent;
class ObjectReturnToPoolEvent;
class ForceOnObjectEvent;
class SceneFadeEvent;
class PauseEvent;
class PlayEvent;
class GoToNextDungeonEvent;

class EventManager
{
	DECLARE_SINGLE(EventManager);

public:
	void AddEvent(unique_ptr<Event> pEvent);
	void ProcessEvents();

private:
	void ProcessSceneChangeEvent(SceneChangeEvent* pEvent);
	void ProcessObjectAddedEvent(ObjectAddedToSceneEvent* pEvent);
	void ProcessObjectRemoveEvent(ObjectRemoveToSceneEvent* pEvent);
	void ProcessObjectReturnToPoolEvent(ObjectReturnToPoolEvent* pEvent);
	void ProcessPlayerChangeStateEvent(PlayerChangeStateEvent* pEvent);
	void ProcessMonsterChangeStateEvent(MonsterChangeStateEvent* pEvent);
	void ProcessForceOnObjectEvent(ForceOnObjectEvent* pEvent);
	void ProcessSceneFadeEvent(SceneFadeEvent* pEvent);
	void ProcessPauseEvent(PauseEvent* pEvent);
	void ProcessPlayEvent(PlayEvent* pEvent);
	void ProcessGoToNextDungeonEvent(GoToNextDungeonEvent* pEvent);

private:
	std::queue<unique_ptr<Event>> m_qEvents;
};

