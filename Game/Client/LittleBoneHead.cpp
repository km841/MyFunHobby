#include "pch.h"
#include "LittleBoneHead.h"

LittleBoneHead::LittleBoneHead()
{
}

LittleBoneHead::~LittleBoneHead()
{
}

void LittleBoneHead::Awake()
{
	PlayerProjectile::Awake();
}

void LittleBoneHead::Start()
{
	PlayerProjectile::Start();
}

void LittleBoneHead::Update()
{
	PlayerProjectile::Update();
}

void LittleBoneHead::LateUpdate()
{
	PlayerProjectile::LateUpdate();
}

void LittleBoneHead::FinalUpdate()
{
	PlayerProjectile::FinalUpdate();
}

void LittleBoneHead::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	int a = 0;
}

void LittleBoneHead::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
