#include "pch.h"
#include "FilterShaders.h"


PxQueryHitType::Enum PlayerFilterShaders::preFilter(
	const PxFilterData& filterData, const PxShape* pShape, const PxRigidActor* pActor, PxHitFlags& queryFlags)
{
	
	// ��Ʈ �߻� �� ó��
	MessageBox(NULL, L"", L"", MB_OK);

	return PxQueryHitType::eTOUCH;
	
}

PxQueryHitType::Enum PlayerFilterShaders::postFilter(const PxFilterData& filterData, const PxQueryHit& queryHit)
{
	return PxQueryHitType::eBLOCK;
}









// =======================
// PlayerSimulationShaders
// =======================
