#pragma once
#include "MapReward.h"
class BoneReward :
    public MapReward
{
public:
    BoneReward(GRADE eGrade);
    virtual ~BoneReward();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    void CreateHoveringKeyAndAddedToScene();
};

