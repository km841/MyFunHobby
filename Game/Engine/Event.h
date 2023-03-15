#pragma once

enum class EVENT_TYPE
{
	SCENE_CHANGE,
	OBJECT_ADDED_TO_SCENE,
	END,
};

class Event
{
public:
	EVENT_TYPE GetEventType() { return m_eEventType; }
	
protected:
	EVENT_TYPE m_eEventType;
};

