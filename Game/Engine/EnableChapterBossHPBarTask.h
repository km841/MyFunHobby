#pragma once
#include "BehaviorTask.h"
class EnableChapterBossHPBarTask :
    public BehaviorTask
{
public:
    EnableChapterBossHPBarTask(shared_ptr<GameObject> pGameObject, STAGE_KIND eStageKind);
    virtual BEHAVIOR_RESULT Run() override;

private:
    STAGE_KIND m_eStageKind;
};

