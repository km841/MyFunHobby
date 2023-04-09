#pragma once
#include "Scene.h"

enum class DRAWING_TYPE : uint8
{
    DRAGGING,
    POINT,
};

enum class OUTPUT_TYPE : uint8
{
    WRITE,
    ERASE,
};

enum class COLLIDER_TYPE : uint8
{
    NONE,
    WALL,
    FOOTHOLD,
};

enum
{
    GRID_SIZE = 1000,
    FRAME_BOX_COUNT = 100,
};

class ToolScene :
    public Scene
{
    using TileMap = std::map<Vec2, bool>;
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

    void LoadTileMap();
    void EraseTileMap();

private:
    void PalleteUpdate();

    void CreateTile(const Vec3& vWorldPos);
    void CreateTile(const Vec2& vTileAlignPos, wstring szTexPath);

    void EraseTile(const Vec3& vWorldPos);
    bool CheckTileAtClick(const Vec3& vWorldPos);

private:
    void AnimationEditorUpdate();
    void SpriteUpdate();
    void DrawEditorGraphic();
    void PlayAnimation();

private:
    shared_ptr<GameObject> m_pPreviewTile;
    shared_ptr<GameObject> m_pMainCamera;
    shared_ptr<GameObject> m_pGrid;
    shared_ptr<GameObject> m_pSpriteTexture;

    Timer m_tTileDragHolder;
    TileMap m_mTileMap;
    TileMapData m_TileMapData;

    std::vector<shared_ptr<GameObject>> m_vFrameDividers;
    
};

