#pragma once
#include "Component.h"

class Material;
class Mesh;
class Camera;
class StructuredBuffer;

struct ParticleInfo
{
	Vec4 vPosition;
	Vec4 vDirection;

	float fEndTime;
	float fCurTime;
	float fSpeed;
	uint32 iAlive;
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
	void SetMesh(shared_ptr<Mesh> pMesh) { m_pMesh = pMesh; }
	void SetMaterial(shared_ptr<Material> pMaterial) { m_pMaterial = pMaterial; }

private:
	shared_ptr<StructuredBuffer> m_pParticleBuffer;
	shared_ptr<StructuredBuffer> m_pSharedBuffer;

	shared_ptr<Mesh> m_pMesh;
	shared_ptr<Material> m_pMaterial;
	shared_ptr<Material> m_pComputeMaterial;

	Vec4 m_vStartScale;
	Vec4 m_vStartColor;

	uint32 m_iMaxParticles;
	float m_fEndTime;
	float m_fStartSpeed;

	// Total Time
	float m_fElapsedTime;
	float m_fAccTime;

	// Step Size
	float m_fCreateInterval;
};

