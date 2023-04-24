#pragma once


class Event
{
public:
	FORCEINLINE EVENT_TYPE GetEventType() { return m_eEventType; }
	
protected:
	EVENT_TYPE m_eEventType;
};

