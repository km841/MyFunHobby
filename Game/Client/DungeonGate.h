#pragma once
#include "GameObject.h"
class DungeonGate :
    public GameObject
{
public:
    friend class DungeonGateOpenEvent;

    explicit DungeonGate(STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType);
    virtual ~DungeonGate();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    STAGE_KIND GetStageKind() { return m_eStageKind; }
    DUNGEON_TYPE GetDungeonType() { return m_eDungeonType; }

public:
    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
    STAGE_KIND m_eStageKind;
    DUNGEON_TYPE m_eDungeonType;
    bool m_bIsCollisionWithPlayer;
    bool m_bOpen;
};

