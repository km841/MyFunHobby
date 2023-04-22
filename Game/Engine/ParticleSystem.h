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
	uint32 iAlive;
	Vec2 vPadding;
};

struct ParticleShared
{
	uint32 iAdd;
};

enum class eSimulationSpace
{
	Local,
	World,
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
	FORCEINLINE void SetParticleScale(const Vec3& vScale) { m_vStartScale = vScale; }
	FORCEINLINE void SetParticleLifeTime(float fLifeTime) { m_fEndTime = fLifeTime; }
	FORCEINLINE void SetCreateInterval(float fCreateInterval) { m_fCreateInterval = fCreateInterval; }
	FORCEINLINE void SetMaxParticles(uint32 iMaxParticles) { m_iMaxParticles = iMaxParticles; }

private:
	shared_ptr<StructuredBuffer> m_pParticleBuffer;
	shared_ptr<StructuredBuffer> m_pSharedBuffer;

	shared_ptr<Mesh> m_pMesh;
	shared_ptr<Material> m_pMaterial;
	shared_ptr<Material> m_pComputeMaterial;

	Vec3 m_vStartScale;

	uint32 m_iMaxParticles;
	float m_fEndTime;
	float m_fStartSpeed;

	// Total Time
	float m_fElapsedTime;
	float m_fAccTime;

	// Step Size
	float m_fCreateInterval;
};

