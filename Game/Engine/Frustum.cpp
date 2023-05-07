#include "pch.h"
#include "Frustum.h"
#include "Camera.h"

void Frustum::FinalUpdate(shared_ptr<Camera> pCamera)
{
	Matrix matViewInv = pCamera->GetViewMatrix();
	Matrix matProjectionInv = pCamera->GetProjectionMatrix();
	Matrix matInv = matProjectionInv.Invert() * matViewInv.Invert();

	std::vector<Vec3> vWorldPos
	{
		XMVector3TransformCoord(Vec3(-1.f, 1.f, 0.f), matInv),
		XMVector3TransformCoord(Vec3(1.f, 1.f, 0.f), matInv),
		XMVector3TransformCoord(Vec3(1.f, -1.f, 0.f), matInv),
		XMVector3TransformCoord(Vec3(-1.f, -1.f, 0.f), matInv),
		XMVector3TransformCoord(Vec3(-1.f, 1.f, 1.f), matInv),
		XMVector3TransformCoord(Vec3(1.f, 1.f, 1.f), matInv),
		XMVector3TransformCoord(Vec3(1.f, -1.f, 1.f), matInv),
		XMVector3TransformCoord(Vec3(-1.f, -1.f, 1.f), matInv)
	};

	m_arrPlanes[PLANE_UP] =    XMPlaneFromPoints(vWorldPos[4], vWorldPos[5], vWorldPos[1]); // CW
	m_arrPlanes[PLANE_DOWN] =  XMPlaneFromPoints(vWorldPos[7], vWorldPos[3], vWorldPos[6]); // CCW
	m_arrPlanes[PLANE_LEFT] =  XMPlaneFromPoints(vWorldPos[4], vWorldPos[0], vWorldPos[7]); // CW
	m_arrPlanes[PLANE_RIGHT] = XMPlaneFromPoints(vWorldPos[5], vWorldPos[6], vWorldPos[1]); // CCW
}

bool Frustum::ContainsSphere(const Vec3& vPos, float fRadius)
{
	for (const Vec4& vPlane : m_arrPlanes)
	{
		// n = (a, b, c)
		Vec3 vNormal = Vec3(vPlane.x, vPlane.y, vPlane.z);

		// ax + by + cz + d > radius
		if (vNormal.Dot(vPos) + vPlane.w > fRadius)
			return false;
	}
	
	return true;
}
