#pragma once
#include "BehaviorTask.h"
class GameObject;
class PatrolTask :
    public BehaviorTask
{
public:
    PatrolTask(shared_ptr<GameObject> pGameObject, float fStartDist, float fEndDist);
    virtual BEHAVIOR_RESULT Run() override;

private:
    float m_fStartDist;
    float m_fEndDist;
    float m_fRandDist;
    
    bool m_bSettingDist;
    bool m_bIsTileInDirection;

    Vec3 m_vPrevPosition;
};

