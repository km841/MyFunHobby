#include "pch.h"
#include "Particle.h"
#include "RigidBody.h"
POOL_INIT(Particle);
Particle::Particle()
	: GameObject(LAYER_TYPE::PARTICLE)
{
}

Particle::~Particle()
{
}

void Particle::Awake()
{
	GameObject::Awake();
}

void Particle::Start()
{
	GameObject::Start();
}

void Particle::Update()
{
	GameObject::Update();
}

void Particle::LateUpdate()
{
	GameObject::LateUpdate();
}

void Particle::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Particle::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		Vec3 vVelocity = GetRigidBody()->GetVelocity();
		if (1.f > vVelocity.Length())
			vVelocity = Vec3::Zero;
		else
			vVelocity /= 2.f;

		GetRigidBody()->SetVelocity(vVelocity);
	}
}

void Particle::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}
