#pragma once
#include "BehaviorCondition.h"
class CloseToTheWallCondition :
    public BehaviorCondition
{
public:
    CloseToTheWallCondition(shared_ptr<GameObject> pGameObject);
    virtual ~CloseToTheWallCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;
};

