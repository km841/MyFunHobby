#include "pch.h"
#include "ReportCallback.h"

void PlayerReportCallback::onShapeHit(const PxControllerShapeHit& hit)
{
	PxRigidActor* pActor = hit.shape->getActor();
	if (pActor)
	{
		const char* szName = pActor->getName();
		PxVec3 vNormal = hit.worldNormal;
		PxExtendedVec3 vPos = hit.worldPos;

		MessageBox(NULL, L"", L"", MB_OK);
	}
}

void PlayerReportCallback::onControllerHit(const PxControllersHit& hit)
{
	int a = 0;
}

void PlayerReportCallback::onObstacleHit(const PxControllerObstacleHit& hit)
{
	int a = 0;
}
