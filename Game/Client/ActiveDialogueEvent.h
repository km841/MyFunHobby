#pragma once
#include "DungeonEvent.h"
class ActiveDialogueEvent :
    public DungeonEvent
{
public:
	ActiveDialogueEvent(shared_ptr<ConditionBlock> pConditionBlock, const wstring& szTalker, const wstring& szLine, float fDuration);
	virtual ~ActiveDialogueEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	wstring m_szTalker;
	wstring m_szLine;
	float m_fDuration;
};

