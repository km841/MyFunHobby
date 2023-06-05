#include "pch.h"
#include "IfFinishedTimer.h"
#include "Clock.h"

IfFinishedTimer::IfFinishedTimer(float fDuration)
    : m_tDuration(fDuration)
{
    m_tDuration.Start();
}

bool IfFinishedTimer::IsTrigger()
{
    m_tDuration.Update(WORLD_DELTA_TIME);
    return m_tDuration.IsFinished() ? true : false;
}
