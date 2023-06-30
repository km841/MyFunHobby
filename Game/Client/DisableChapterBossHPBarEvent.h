#pragma once
#include "DungeonEvent.h"
class DisableChapterBossHPBarEvent :
    public DungeonEvent
{
public:
	DisableChapterBossHPBarEvent(shared_ptr<ConditionBlock> pConditionBlock);
	virtual ~DisableChapterBossHPBarEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();
};

