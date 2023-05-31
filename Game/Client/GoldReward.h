#pragma once
#include "MapReward.h"
class GoldReward :
    public MapReward
{
public:
    GoldReward();
    virtual ~GoldReward();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    void ScatterGold();

private:
    void CreateHoveringKeyAndAddedToScene();
};

