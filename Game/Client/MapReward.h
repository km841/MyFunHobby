#pragma once
#include "GameObject.h"
class MapReward :
    public GameObject
{
public:
    MapReward(GRADE eGrade);
    virtual ~MapReward();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    GRADE m_eGrade;
};

