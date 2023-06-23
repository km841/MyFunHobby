#pragma once
#include "DungeonEvent.h"
class PlayBGMEvent :
    public DungeonEvent
{
public:
	PlayBGMEvent(shared_ptr<ConditionBlock> pConditionBlock, const wstring& szBgmPath);
	virtual ~PlayBGMEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	wstring m_szBgmPath;
};

