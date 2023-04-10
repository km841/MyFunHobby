#pragma once
#include "Skul.h"
class GlobalEffect;
class AbyssMeteor;
class HighWarlock :
    public Skul
{
public:
	HighWarlock();
	virtual ~HighWarlock() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

public:
	FORCEINLINE weak_ptr<GlobalEffect> GetAbyssField() { return m_pAbyssField; }
	void ActiveAbyssField();
	void DeActiveAbyssField();

private:
	void CreateEffectAndAddedToScene();

private:
	shared_ptr<GlobalEffect> m_pAbyssField;
};

