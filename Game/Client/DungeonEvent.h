#pragma once
class ConditionBlock;
class DungeonEvent
{
public:
	DungeonEvent(DUNGEON_EVENT_KIND eEventKind, shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~DungeonEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent() = 0;

	bool IsTrigger() { return m_bIsTrigger; }

private:
	DUNGEON_EVENT_KIND m_eEventKind;
	shared_ptr<ConditionBlock> m_pConditionBlock;
	bool m_bIsTrigger;
};

