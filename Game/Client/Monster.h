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

	FORCEINLINE MONSTER_STATE GetMonsterState() { return m_eMonsterState; }
	FORCEINLINE void		  SetMonsterState(MONSTER_STATE eMonsterState) { m_eMonsterState = eMonsterState; }

	FORCEINLINE MONSTER_TYPE GetMonsterType() { return m_eMonsterType; }

	FORCEINLINE const Vec3&   GetParticleDir() { return m_vParticleDir; }
	FORCEINLINE void		  SetParticleDir(const Vec3& vDir) { m_vParticleDir = vDir; }

	FORCEINLINE bool GetDeadFlag() { return m_bDeadFlag; }
	FORCEINLINE void SetDeadFlag(bool bDeadFlag) { m_bDeadFlag = bDeadFlag; }

public:
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);
	virtual void ScatterParticles(PARTICLE_DIRECTION eParticleDirection) { }
	virtual void ActivateDeadEvent(PARTICLE_DIRECTION eParticleDirection);
	virtual void ScatterParticles(const Vec3& vDir) { }
	virtual void ScatterGold();
	virtual void ScatterDarkQuartz();
	virtual void ActivateDeadEvent(const Vec3& vDir);
	virtual void ActivateDeadEvent();

public:
	void SetParticleTextureNames(const std::vector<wstring> vTextureNames) { m_vTextureNames = vTextureNames; }
	weak_ptr<GlobalEffect> GetParticleGenerator() { return m_pParticleGenerator; }

protected:
	int32 CalculateParticleDirectionToDegree(PARTICLE_DIRECTION eParticleDirection);
	void CreateMonsterHPHUD();
	void CreateDeadEffectAndAddedScene();
	void CreateParticleGeneratorAndAddedToScene();
	void SetMonsterHPBarWidthAndUnder(float fWidth, float fUnder);

protected:
	bool m_bHitFlag;
	bool m_bExtraHitFlag;
	bool m_bDeadFlag;

	Vec3 m_vParticleDir;

	shared_ptr<MonsterHPHUD> m_pMonsterHPHUDFrame;
	shared_ptr<MonsterHPHUD> m_pMonsterHPHUD;

	std::vector<wstring> m_vTextureNames;
	shared_ptr<GlobalEffect> m_pParticleGenerator;

	MONSTER_STATE m_eMonsterState;
	MONSTER_TYPE m_eMonsterType;

};

