#pragma once
class PhysicsScene
{
public:
	explicit PhysicsScene(PxScene* pScene);
	~PhysicsScene();

public:
	FORCEINLINE PxScene* GetScene() { return m_pScene; }

public:
	void AddActor(PxActor* pActor);
	void RemoveActor(PxActor* pActor);

public:
	RaycastResult Raycast(Vec3 vOrigin, Vec3 vDir, float fMaxDistance);

private:
	PxScene* m_pScene;

	PxRaycastBuffer m_RaycastBuffer;
	PxSweepBuffer   m_SweepBuffer;
	PxOverlapBuffer m_OverlapBuffer;

	float		    m_fMaxDistance;
};

