#include "pch.h"
#include "ParticleSystem.h"
#include "StructuredBuffer.h"
#include "Mesh.h"
#include "Resources.h"
#include "Transform.h"
#include "Clock.h"
#include "Engine.h"

ParticleSystem::ParticleSystem()
	: Component(COMPONENT_TYPE::PARTICLE_SYSTEM)
	, m_iMaxParticles(1000)
	, m_fEndTime(1.f)
	, m_fAccTime(0.f)
	, m_fStartSpeed(300.0f)
	, m_fEndSpeed(700.f)
	, m_fElapsedTime(0.f)
	, m_fCreateInterval(1.f)
	, m_vStartScale(4.f, 4.f, 1.f)
	, m_fGravity(-5.f)
	, m_iAliveCount(0)
	, m_fStartAngle(70.f)
	, m_fEndAngle(90.f)
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Awake()
{
	m_pMesh = GET_SINGLE(Resources)->LoadPointMesh();
	m_pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Particle");
	m_pComputeMaterial = GET_SINGLE(Resources)->Get<Material>(L"ComputeParticle");
	
	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"Bubble", L"..\\Resources\\Texture\\Particle\\Image_Particle.png");
	m_pMaterial->SetTexture(0, pTexture);

	std::vector<ParticleInfo> vParticles(m_iMaxParticles);
	m_pParticleBuffer = make_shared<StructuredBuffer>();
	m_pParticleBuffer->Create(sizeof(ParticleInfo), m_iMaxParticles, vParticles.data());

	m_pSharedBuffer = make_shared<StructuredBuffer>();
	m_pSharedBuffer->Create(sizeof(ParticleShared), 1, nullptr, true);
}

void ParticleSystem::Update()
{
}

void ParticleSystem::FinalUpdate()
{
	m_fElapsedTime += DELTA_TIME;

	if (m_iAliveCount > 0)
	{
		ParticleShared shared = { m_iAliveCount, }; // 활성화시킬 파티클의 수
		m_pSharedBuffer->SetData(&shared, 1);
		m_iAliveCount = 0;
	}

	else
	{
		ParticleShared shared = {  };
		m_pSharedBuffer->SetData(&shared, 1);
	}

	Vec3 vPosition = GetTransform()->GetWorldPosition();
	m_iMaxParticles = m_pParticleBuffer->GetElementCount();
	m_pComputeMaterial->SetVec3(0, GetTransform()->GetWorldPosition());
	m_pComputeMaterial->SetVec3(1, m_vStartDir);
	m_pComputeMaterial->SetInt(0, m_iMaxParticles);
	m_pComputeMaterial->SetFloat(0, m_fEndTime);
	m_pComputeMaterial->SetFloat(1, m_fGravity);
	m_pComputeMaterial->SetVec2(0, Vec2(DELTA_TIME, m_fElapsedTime));
	m_pComputeMaterial->SetVec2(1, Vec2(m_fStartSpeed, m_fEndSpeed));
	m_pComputeMaterial->SetVec2(2, Vec2(m_fStartAngle, m_fEndAngle));

	m_pParticleBuffer->PushComputeUAVData(UAV_REGISTER::u0);
	m_pSharedBuffer->PushComputeUAVData(UAV_REGISTER::u1);
	m_pComputeMaterial->Dispatch(1, 1, 1);
}

void ParticleSystem::Render(shared_ptr<Camera> pCamera)
{
	GetTransform()->PushData(pCamera);
	m_pParticleBuffer->PushGraphicsData(SRV_REGISTER::t9);

	m_pMaterial->PushGraphicData();
	m_pMaterial->SetVec3(0, m_vStartScale);
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->Mapping();
	m_pMesh->Render(m_iMaxParticles);

	m_pParticleBuffer->ClearGraphicsData();
}

void ParticleSystem::SetParticleDirection(PARTICLE_DIRECTION eParticleDirection)
{
	switch (eParticleDirection)
	{
	case PARTICLE_DIRECTION::TOP:
		m_fStartAngle = 75.f;
		m_fEndAngle = 105.f;
		break;
	case PARTICLE_DIRECTION::RIGHT_TOP:
		m_fStartAngle = 60.f;
		m_fEndAngle = 90.f;
		break;
	case PARTICLE_DIRECTION::RIGHT:
		m_fStartAngle = 60.f;
		m_fEndAngle = 90.f;
		break;
	case PARTICLE_DIRECTION::RIGHT_BTM:
		m_fStartAngle = -30.f;
		m_fEndAngle = -60.f;
		break;
	case PARTICLE_DIRECTION::BTM:
		m_fStartAngle = -75.f;
		m_fEndAngle = -105.f;
		break;
	case PARTICLE_DIRECTION::LEFT_BTM:
		m_fStartAngle = 120.f;
		m_fEndAngle = 150.f;
		break;
	case PARTICLE_DIRECTION::LEFT:
		m_fStartAngle = -240.f;
		m_fEndAngle = -270.f;
		break;
	case PARTICLE_DIRECTION::LEFT_TOP:
		m_fStartAngle = -240.f;
		m_fEndAngle = -270.f;
		break;
	}
}
