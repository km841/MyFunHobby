#include "pch.h"
#include "PhysicsScene.h"

PhysicsScene::PhysicsScene(PxScene* pScene)
	: m_pScene(pScene)
{
}

PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::AddActor(PxActor* pActor)
{
	assert(m_pScene);
	m_pScene->addActor(*pActor);
}

void PhysicsScene::RemoveActor(PxActor* pActor)
{
	assert(m_pScene);
	m_pScene->removeActor(*pActor);
}
