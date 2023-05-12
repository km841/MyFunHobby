#pragma once
#include "MapReward.h"
class TreasureBox :
    public MapReward
{
public:
    TreasureBox(GRADE eGrade);
    virtual ~TreasureBox();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

