#include "pch.h"
#include "PxEnvironment.h"

PxEnvironment::PxEnvironment()
	: m_pScene(nullptr)
	, m_pControllerMgr(nullptr)
{
	m_pSetting = make_shared<PxEnvironmentSetting>();
}

PxEnvironment::~PxEnvironment()
{
	if (m_pControllerMgr)
		m_pControllerMgr->release();

	if (m_pPvd)
		m_pPvd->release();

	if (m_pTransfort)
		m_pTransfort->release();

	if (m_pScene)
		m_pScene->release();
}

void PxEnvironment::Init()
{
	m_pSetting->CreateFoundation();
	m_pSetting->CreatePhysics();

	
	CreateDebugger("127.0.0.1", 5425); 
	ConnectDebugger();
}

void PxEnvironment::CreateControllerManager()
{
	assert(m_pScene);
	m_pControllerMgr = PxCreateControllerManager(*m_pScene);
}

void PxEnvironment::CreateDebugger(const char* szHost, int32 iPort)
{
	m_pTransfort = PxDefaultPvdSocketTransportCreate(szHost, iPort, 10);
	assert(m_pTransfort);
}

void PxEnvironment::ConnectDebugger()
{
	m_pPvd = PxCreatePvd(*m_pSetting->GetFoundation());
	m_pPvd->connect(*m_pTransfort, PxPvdInstrumentationFlag::eALL);
}

void PxEnvironment::ConnectDebuggerToScene()
{
	m_pSceneClient = m_pScene->getScenePvdClient();
	assert(m_pSceneClient);

	m_pSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
	m_pSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
	m_pSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
}

void PxEnvironment::CreatePhysicsScene(const PxSceneDesc& sceneDesc)
{
	CreateScene(sceneDesc);
	CreateControllerManager();

	assert(m_pScene);
	m_pPhysScene = make_shared<PhysicsScene>(m_pScene);
}

void PxEnvironment::CreateScene(const PxSceneDesc& sceneDesc)
{
	assert(m_pSetting->GetPhysics());
	m_pScene = m_pSetting->GetPhysics()->createScene(sceneDesc);
}