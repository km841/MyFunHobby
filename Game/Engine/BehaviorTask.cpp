#include "pch.h"
#include "BehaviorTask.h"

BehaviorTask::BehaviorTask(std::function<BEHAVIOR_RESULT()> fnTask)
    : m_fnTask(fnTask)
{
}

BEHAVIOR_RESULT BehaviorTask::Run()
{
    return m_fnTask();
}
