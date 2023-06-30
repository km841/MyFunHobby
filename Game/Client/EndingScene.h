#pragma once
#include "Scene.h"
class EndingScene :
    public Scene
{
public:
    EndingScene();
    virtual ~EndingScene();

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
};

