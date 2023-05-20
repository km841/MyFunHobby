#include "pch.h"
#include "ErodedHeavyInfantry.h"

POOL_INIT(ErodedHeavyInfantry);
ErodedHeavyInfantry::ErodedHeavyInfantry()
{
}

ErodedHeavyInfantry::~ErodedHeavyInfantry()
{
}

void ErodedHeavyInfantry::Awake()
{
	Monster::Awake();
}

void ErodedHeavyInfantry::Start()
{
	Monster::Start();
}

void ErodedHeavyInfantry::Update()
{
	Monster::Update();
}

void ErodedHeavyInfantry::LateUpdate()
{
	Monster::LateUpdate();
}

void ErodedHeavyInfantry::FinalUpdate()
{
	Monster::FinalUpdate();
}

void ErodedHeavyInfantry::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
}

void ErodedHeavyInfantry::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void ErodedHeavyInfantry::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

void ErodedHeavyInfantry::ScatterParticles(const Vec3& vDir)
{
}

void ErodedHeavyInfantry::ActivateDeadEvent(const Vec3& vDir)
{
}
