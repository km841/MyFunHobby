#include "pch.h"
#include "ErodedEnt.h"

ErodedEnt::ErodedEnt()
{
}

ErodedEnt::~ErodedEnt()
{
}

void ErodedEnt::Awake()
{
	Monster::Awake();
}

void ErodedEnt::Start()
{
	Monster::Start();
}

void ErodedEnt::Update()
{
	Monster::Update();
}

void ErodedEnt::LateUpdate()
{
	Monster::LateUpdate();
}

void ErodedEnt::FinalUpdate()
{
	Monster::FinalUpdate();
}

void ErodedEnt::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
}

void ErodedEnt::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void ErodedEnt::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

void ErodedEnt::ScatterParticles(const Vec3& vDir)
{
}

void ErodedEnt::ActivateDeadEvent(const Vec3& vDir)
{
}

void ErodedEnt::ActivateDeadEvent()
{
}
