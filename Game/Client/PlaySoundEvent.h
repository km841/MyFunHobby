#pragma once
#include "DungeonEvent.h"
class PlaySoundEvent :
    public DungeonEvent
{
public:
	PlaySoundEvent(shared_ptr<ConditionBlock> pConditionBlock, const wstring& szBgmPath);
	virtual ~PlaySoundEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	wstring m_szSoundPath;
};

