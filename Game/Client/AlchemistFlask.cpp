#include "pch.h"
#include "AlchemistFlask.h"

POOL_INIT(AlchemistFlask);
AlchemistFlask::AlchemistFlask()
{
}

AlchemistFlask::~AlchemistFlask()
{
}

void AlchemistFlask::Awake()
{
	MonsterProjectile::Awake();
}

void AlchemistFlask::Start()
{
	MonsterProjectile::Start();
}

void AlchemistFlask::Update()
{
	MonsterProjectile::Update();
}

void AlchemistFlask::LateUpdate()
{
	MonsterProjectile::LateUpdate();
}

void AlchemistFlask::FinalUpdate()
{
	MonsterProjectile::FinalUpdate();
}

void AlchemistFlask::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void AlchemistFlask::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
