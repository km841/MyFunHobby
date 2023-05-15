#pragma once
#include "GameObject.h"

class GlobalEffect;
class Particle;
class Texture;
class MonsterHPHUD;

class Monster :
    public GameObject
{
public:
	Monster();
	virtual ~Monster();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

public:
	FORCEINLINE bool IsHitFlag()		{ return m_bHitFlag; }
	FORCEINLINE void FlagAsAttacked()   { m_bHitFlag = true; }
	FORCEINLINE void UnflagAsAttacked() { m_bHitFlag = false; }

	FORCEINLINE bool IsExtraHitFlag() { return m_bExtraHitFlag; }
	FORCEINLINE void FlagAsExtraAttacked() { m_bExtraHitFlag = true; }
	FORCEINLINE void UnflagAsExtraAttacked() { m_bExtraHitFlag = false; }

public:
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);
	virtual void ScatterParticles(PARTICLE_DIRECTION eParticleDirection) { }
	virtual void ActivateDeadEvent(PARTICLE_DIRECTION eParticleDirection);
	virtual void ScatterParticles(const Vec3& vDir) { }
	virtual void ActivateDeadEvent(const Vec3& vDir);

public:
	void SetParticleTextureNames(const std::vector<wstring> vTextureNames) { m_vTextureNames = vTextureNames; }
	weak_ptr<GlobalEffect> GetParticleGenerator() { return m_pParticleGenerator; }

protected:
	int32 CalculateParticleDirectionToDegree(PARTICLE_DIRECTION eParticleDirection);
	void CreateMonsterHPHUD();
	void CreateDeadEffectAndAddedScene();
	void CreateParticleGeneratorAndAddedToScene();

protected:
	bool m_bHitFlag;
	bool m_bExtraHitFlag;

	shared_ptr<MonsterHPHUD> m_pMonsterHPHUDFrame;
	shared_ptr<MonsterHPHUD> m_pMonsterHPHUD;

	std::vector<wstring> m_vTextureNames;
	shared_ptr<GlobalEffect> m_pParticleGenerator;
};

