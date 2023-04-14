#pragma once
#include "Selector.h"
class ChasePlayerSelector :
    public Selector
{
public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    bool IsPlayerInRange();

};

