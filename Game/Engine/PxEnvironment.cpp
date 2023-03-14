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

	if (m_pScene)
		m_pScene->release();
}

void PxEnvironment::Init()
{
	m_pSetting->CreateFoundation();
	m_pSetting->CreatePhysics();

	CreateSceneQuery();
}

void PxEnvironment::CreateControllerManager()
{
	assert(m_pScene);
	m_pControllerMgr = PxCreateControllerManager(*m_pScene);
}

void PxEnvironment::CreateSceneQuery()
{
	// PxSceneQuery 내용 초기화
	m_pSceneQuery = make_shared<PxSceneQuery>();





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