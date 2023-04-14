#pragma once
#include "Sequence.h"
class FleeSequence :
    public Sequence
{
public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    void StopSkill();
    bool IsPlayerOutOfRange();

};

