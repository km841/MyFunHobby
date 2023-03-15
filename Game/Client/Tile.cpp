#include "pch.h"
#include "Tile.h"

POOL_INIT(Tile);
Tile::Tile()
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
