#include "pch.h"
#include "Tile.h"

POOL_INIT(Tile);
Tile::Tile(TILE_TYPE eTileType)
	: GameObject(LAYER_TYPE::TILE)
	, m_eTileType(eTileType)
{
}

Tile::~Tile()
{
}

void Tile::Awake()
{
	GameObject::Awake();
}

void Tile::Start()
{
	GameObject::Start();
}

void Tile::Update()
{
	GameObject::Update();
}

void Tile::LateUpdate()
{
	GameObject::LateUpdate();
}

void Tile::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Tile::Init(int32 iTileType)
{
	m_eTileType = static_cast<TILE_TYPE>(iTileType);
}
