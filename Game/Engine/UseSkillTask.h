#pragma once
#include "BehaviorTask.h"
class UseSkillTask :
    public BehaviorTask
{
public:
    UseSkillTask(std::function<BEHAVIOR_RESULT()> fnTask);
    virtual BEHAVIOR_RESULT Run() override;

private:
    void UseSkill();
};

