#pragma once
#include "BehaviorTask.h"
class PlaySoundTask :
    public BehaviorTask
{
public:
    PlaySoundTask(shared_ptr<GameObject> pGameObject, const wstring& szSoundPath);
    virtual BEHAVIOR_RESULT Run() override;

private:
    wstring m_szSoundPath;
};

