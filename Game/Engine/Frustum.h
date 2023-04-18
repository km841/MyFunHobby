#pragma once

enum PLANE_TYPE : uint8
{
	PLANE_FRONT,
	PLANE_BACK,
	PLANE_UP,
	PLANE_DOWN,
	PLANE_LEFT,
	PLANE_RIGHT,

	PLANE_END
};

class Camera;
class Frustum
{
public:
	void FinalUpdate(shared_ptr<Camera> pCamera);
	bool ContainsSphere(const Vec3& vPos, float fRadius);

private:
	std::array<Vec4, PLANE_END> m_arrPlanes;
};

