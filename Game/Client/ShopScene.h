#pragma once
#include "Scene.h"
class ShopScene :
    public Scene
{
public:
    ShopScene();
    virtual ~ShopScene();

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

