#pragma once
#include "BehaviorTask.h"
class MoveTask :
    public BehaviorTask
{
public:
    MoveTask(std::function<BEHAVIOR_RESULT()> fnTask);
    virtual BEHAVIOR_RESULT Run() override;

private:
};

