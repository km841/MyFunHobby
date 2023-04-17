#include "pch.h"
#include "Physics.h"
#include "Clock.h"
#include "ContactCallback.h"
#include "Engine.h"

Physics::Physics()
	: m_pEnvironment(nullptr)
	, m_pDispatcher(nullptr)
{
	m_pEnvironment = make_shared<PxEnvironment>();
	m_pDispatcher  = make_shared<PxDispatcher>();
}

Physics::~Physics()
{
	//PxCloseExtensions();
}

void Physics::Init(bool bUseDebugger)
{
	m_bUseDebugger = bUseDebugger;
	m_pEnvironment->Init();

	m_pDispatcher->CreateCpuDispatcher();
	PxSceneDesc sceneDesc(m_pEnvironment->GetPhysics()->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f * 30.f, 0.0f);
	sceneDesc.cpuDispatcher = m_pDispatcher->GetCpuDispatcher();
	sceneDesc.filterShader = PlayerFilterShader;
	sceneDesc.simulationEventCallback = m_pDispatcher->GetSimulationCallback();

	m_pEnvironment->CreatePhysicsScene(sceneDesc);
	m_pEnvironment->ConnectDebuggerToScene();
}

void Physics::Update()
{
	GetScene()->simulate(DELTA_TIME);
	GetScene()->fetchResults(true);
}

PxScene* Physics::GetScene()
{
	return m_pEnvironment->GetPhysScene()->GetScene();
}
