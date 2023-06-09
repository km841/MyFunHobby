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

using DungeonObjPair = std::pair<STAGE_KIND, DUNGEON_TYPE>;

class Background;
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
    void MapEditorUpdate();

    void CreateTile(const Vec3& vWorldPos, TILE_TYPE eTileType);
    void CreateTile(const Vec2& vTileAlignPos, wstring szTexPath, TILE_TYPE eTileType);

    void CreateDungeonGate(const Vec3& vWorldPos, const wstring& szSelectedKey);
    void CreateDungeonGate(const Vec3& vWorldPos, STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType, const wstring& szTexPath);
    void CreateDungeonGate(const Vec3& vWorldPos, STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType);
    void CreateDungeonWall(const Vec3& vWorldPos, const wstring& szSelectedKey);
    void CreateDungeonWall(const Vec3& vWorldPos, STAGE_KIND eStageKind);
    void CreateDecoObject(const Vec3& vWorldPos, const wstring& szSelectedKey);
    void CreateLightObject(const Vec3& vWorldPos);
    void CreateLightObject(const LightData& lightData);

    void EraseTile(const Vec3& vWorldPos);
    bool CheckTileAtClick(const Vec3& vWorldPos);

    void CreateBGAndAddedToScene(const Vec3& vWorldPos, const Vec3& vWorldScale, const Vec3& vSpeed, const wstring& szBGImagePath);
    void EraseAllBackground();
    void LoadBackgrounds();

    SRV_KIND GetSelectedSRVKind(const wstring& szSRVKey);
    DungeonObjPair WstringToDungeonObjPair(const wstring& szSelectedKey);

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
    std::vector<BackgroundData> m_vBackgroundDataList;

    std::vector<shared_ptr<GameObject>> m_vFrameDividers;
    std::vector<shared_ptr<Background>> m_vBackgrounds;

    bool m_bShowMousePos;
    bool m_bTileAlignMode;
};

