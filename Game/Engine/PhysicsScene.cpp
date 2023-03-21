#include "pch.h"
#include "PhysicsScene.h"

PhysicsScene::PhysicsScene(PxScene* pScene)
	: m_pScene(pScene)
	, m_fMaxDistance(1000.f)
	, m_RaycastBuffer{}
	, m_SweepBuffer{}
	, m_OverlapBuffer{}
{}

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

RaycastResult PhysicsScene::Raycast(Vec3 vOrigin, Vec3 vDir)
{
	bool bResult = m_pScene->raycast(
		Conv::Vec3ToPxVec3(vOrigin),
		Conv::Vec3ToPxVec3(vDir),
		m_fMaxDistance,
		m_RaycastBuffer);

	return RaycastResult(bResult, Conv::PxVec3ToVec3(m_RaycastBuffer.block.position));
}
