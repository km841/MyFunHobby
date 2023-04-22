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
	, m_fEndTime(3.f)
	, m_fAccTime(0.f)
	, m_fStartSpeed(300.0f)
	, m_fElapsedTime(0.f)
	, m_fCreateInterval(0.01f)
	, m_vStartScale(4.f, 4.f, 1.f)
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
	m_fAccTime += DELTA_TIME;
	if (m_fCreateInterval < m_fAccTime)
	{
		m_fAccTime -= m_fCreateInterval;
		ParticleShared shared = { 1, }; // 활성화시킬 파티클의 수
		// WriteBuffer를 이용하여 SharedBuffer에 값을 쓴다
		m_pSharedBuffer->SetData(&shared, 1);
	}
	else
	{
		ParticleShared shared = {  };
		m_pSharedBuffer->SetData(&shared, 1);
	}

	m_iMaxParticles = m_pParticleBuffer->GetElementCount();
	m_pComputeMaterial->SetVec3(0, GetTransform()->GetLocalPosition());
	m_pComputeMaterial->SetInt(0, m_iMaxParticles);
	m_pComputeMaterial->SetFloat(1, m_fStartSpeed);
	m_pComputeMaterial->SetFloat(2, m_fEndTime);
	m_pComputeMaterial->SetVec2(0, Vec2(DELTA_TIME, m_fElapsedTime));
	
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
