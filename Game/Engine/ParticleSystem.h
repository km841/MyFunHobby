#pragma once
#include "Component.h"

class Material;
class Mesh;
class Camera;
class StructuredBuffer;

struct ParticleInfo
{
	Vec3 vPosition;
	float fEndTime;
	Vec3 vDirection;
	float fCurTime;

	float fSpeed;
	float fGravityAcc;
	uint32 iAlive;
	float fPadding;
};

struct ParticleShared
{
	uint32 iAdd;
};

class ParticleShader;
class Camera;
class ParticleSystem : public Component
{
public:
	ParticleSystem();
	~ParticleSystem();

	virtual void Awake() override;
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(shared_ptr<Camera> pCamera);

public:
	FORCEINLINE void SetParticleAliveCount(uint32 iCount) { m_iAliveCount = iCount; }
	FORCEINLINE void SetParticleScale(const Vec3& vScale) { m_vStartScale = vScale; }
	FORCEINLINE void SetParticleLifeTime(float fLifeTime) { m_fEndTime = fLifeTime; }
	FORCEINLINE void SetCreateInterval(float fCreateInterval) { m_fCreateInterval = fCreateInterval; }
	FORCEINLINE void SetMaxParticles(uint32 iMaxParticles) { m_iMaxParticles = iMaxParticles; }

	void SetParticleDirection(PARTICLE_DIRECTION eParticleDirection);
private:
	shared_ptr<StructuredBuffer> m_pParticleBuffer;
	shared_ptr<StructuredBuffer> m_pSharedBuffer;

	shared_ptr<Mesh> m_pMesh;
	shared_ptr<Material> m_pMaterial;
	shared_ptr<Material> m_pComputeMaterial;

	Vec3 m_vStartScale;
	Vec3 m_vStartDir;

	uint32 m_iAliveCount;
	uint32 m_iMaxParticles;
	float m_fEndTime;
	float m_fStartSpeed;
	float m_fEndSpeed;

	float m_fStartAngle;
	float m_fEndAngle;

	float m_fGravity;

	// Total Time
	float m_fElapsedTime;
	float m_fAccTime;

	// Step Size
	float m_fCreateInterval;
};

