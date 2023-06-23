#pragma once
#include "BehaviorTask.h"
class Player;
class MonsterHitFrameProcessingTask :
    public BehaviorTask
{
public:
    MonsterHitFrameProcessingTask(shared_ptr<GameObject> pGameObject, const Vec3& vOffset, const Vec3& vVolume, float fDamage, float fMaxDamage = 0.f, const wstring& szHitSoundPath = L"");
    virtual BEHAVIOR_RESULT Run() override;

private:
    float m_fDamage;
    float m_fMaxDamage;
    Vec3 m_vVolume;
    Vec3 m_vOffset;
    wstring m_szHitSoundPath;
};

