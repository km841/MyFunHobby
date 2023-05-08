#pragma once
#include "GameObject.h"

class Tile :
    public GameObject
{
public:
    Tile(TILE_TYPE eTileType = TILE_TYPE::NONE);
    virtual ~Tile();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();

    virtual void Init(int32 iTileType);

    TILE_TYPE GetTileType() { return m_eTileType; }

private:
    TILE_TYPE m_eTileType;

private:
    DECLARE_POOL(Tile);

};

