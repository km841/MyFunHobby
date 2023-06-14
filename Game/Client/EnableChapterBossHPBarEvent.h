#pragma once
#include "DungeonEvent.h"
class EnableChapterBossHPBarEvent :
    public DungeonEvent
{
public:
	EnableChapterBossHPBarEvent(shared_ptr<ConditionBlock> pConditionBlock, STAGE_KIND eStageKind);
	virtual ~EnableChapterBossHPBarEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	STAGE_KIND m_eStageKind;
};

