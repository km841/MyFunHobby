#pragma once
#include "DungeonEvent.h"
class Monster;
class EnableChapterBossHPBarEvent :
    public DungeonEvent
{
public:
	EnableChapterBossHPBarEvent(shared_ptr<ConditionBlock> pConditionBlock, STAGE_KIND eStageKind, shared_ptr<Monster> pBoss);
	virtual ~EnableChapterBossHPBarEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	STAGE_KIND m_eStageKind;
	weak_ptr<Monster> m_pBoss;
};

