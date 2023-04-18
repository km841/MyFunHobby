#pragma once
#include "Event.h"
class SceneChangeEvent;
class ObjectAddedToSceneEvent;
class PlayerChangeStateEvent;
class ObjectRemoveToSceneEvent;
class ObjectReturnToPoolEvent;

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

private:
	std::queue<unique_ptr<Event>> m_qEvents;
};

