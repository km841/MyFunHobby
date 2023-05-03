#pragma once
#include "Scene.h"
class Stage;
class DungeonScene :
    public Scene
{
public:
    DungeonScene();
    virtual ~DungeonScene();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();

private:
    std::array<shared_ptr<Stage>, STAGE_KIND_COUNT> m_arrStages;
    weak_ptr<Stage> m_pActiveStage;

};

