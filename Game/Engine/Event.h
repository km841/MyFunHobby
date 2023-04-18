#pragma once

enum class EVENT_TYPE
{
	SCENE_CHANGE,
	OBJECT_ADDED_TO_SCENE,
	OBJECT_REMOVE_TO_SCENE,
	OBJECT_RETURN_TO_POOL,
	PLAYER_CHANGE_STATE,
	END,
};

class Event
{
public:
	FORCEINLINE EVENT_TYPE GetEventType() { return m_eEventType; }
	
protected:
	EVENT_TYPE m_eEventType;
};

