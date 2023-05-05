#pragma once
#include "Scene.h"
class ShopScene :
    public Scene
{
public:
    ShopScene();
    virtual ~ShopScene();

public:
    virtual void Awake() override;
    virtual void Start() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void FinalUpdate() override;
    virtual void Render() override;

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void InitializeCameraAndPlayerPos() override;
};

