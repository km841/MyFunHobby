#include "pch.h"
#include "MonsterProjectile.h"

MonsterProjectile::MonsterProjectile()
	: GameObject(LAYER_TYPE::MONSTER_PROJECTILE)
{
}

MonsterProjectile::~MonsterProjectile()
{
}

void MonsterProjectile::Awake()
{
	GameObject::Awake();
}

void MonsterProjectile::Start()
{
	GameObject::Start();
}

void MonsterProjectile::Update()
{
	GameObject::Update();
}

void MonsterProjectile::LateUpdate()
{
	GameObject::LateUpdate();
}

void MonsterProjectile::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void MonsterProjectile::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void MonsterProjectile::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
