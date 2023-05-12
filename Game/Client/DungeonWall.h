#pragma once
#include "GameObject.h"
class DungeonWall :
    public GameObject
{
public:
    explicit DungeonWall(STAGE_KIND eStageKind);
    virtual ~DungeonWall();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    FORCEINLINE STAGE_KIND GetStageKind() { return m_eStageKind; }

private:
    STAGE_KIND m_eStageKind;
};

