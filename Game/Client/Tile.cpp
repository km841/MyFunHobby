#include "pch.h"
#include "Tile.h"

POOL_INIT(Tile);
Tile::Tile()
{
	m_eLayerType = LAYER_TYPE::TILE;
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

void Tile::Save(const wstring& szPath)
{
	
}

void Tile::Load(const wstring& szPath)
{
}
