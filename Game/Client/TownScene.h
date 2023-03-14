#pragma once
#include "Scene.h"
class TownScene :
    public Scene
{
public:
    TownScene();
    virtual ~TownScene();

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

};

