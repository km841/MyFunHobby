#pragma once
#include "Skul.h"
class GlobalEffect;
class AnimationLocalEffectOtherLayer;
class AbyssMeteor;
class HighWarlock :
    public Skul
{
public:
	HighWarlock(const SkulInfo& skulInfo);
	virtual ~HighWarlock() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

public:
	FORCEINLINE weak_ptr<GlobalEffect> GetTrailEffect() { return m_pTrailEffect; }
	FORCEINLINE weak_ptr<GlobalEffect> GetChargedEffect() { return m_pChargedEffect; }

	void EnableAndInitTrailEffect();
	void DisableTrailEffect();
	void EnableAndInitChargedEffect();
	void CreateCompletedSmokeAndAddedToScene();
	void CreateAbyssFieldAndAddedToScene();
private:
	
	void CreateTrailEffectAndAddedToScene();
	void CreateChargedEffectAndAddedToScene();

	void TrailAndChargedEffectPositionUpdate();

private:
	shared_ptr<GlobalEffect> m_pTrailEffect;
	shared_ptr<GlobalEffect> m_pChargedEffect;
};

