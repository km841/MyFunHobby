#include "pch.h"
#include "PlayerProjectile.h"

PlayerProjectile::PlayerProjectile()
	: GameObject(LAYER_TYPE::PLAYER_PROJECTILE)
{
}

PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::Awake()
{
	GameObject::Awake();
}

void PlayerProjectile::Start()
{
	GameObject::Start();
}

void PlayerProjectile::Update()
{
	GameObject::Update();
}

void PlayerProjectile::LateUpdate()
{
	GameObject::LateUpdate();
}

void PlayerProjectile::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void PlayerProjectile::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	int a = 0;
}

void PlayerProjectile::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
