#pragma once
#include "Scene.h"

enum class DRAWING_TYPE : uint8
{
    DRAGGING,
    POINT,
};

enum class COLLIDER_TYPE : uint8
{
    NONE,
    WALL,
    FOOTHOLD,
};

class ToolScene :
    public Scene
{
public:
    ToolScene();
    virtual ~ToolScene();

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

public:
    void PalleteUpdate();
    void CreateTile(Vec3 vWorldPos);

private:
    shared_ptr<GameObject> m_pPreviewTile;
    shared_ptr<GameObject> m_pMainCamera;
    shared_ptr<GameObject> m_pGrid;
};

