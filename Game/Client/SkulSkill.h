#pragma once
#include "GameObject.h"
class SkulSkill :
    public GameObject
{
public:
	explicit SkulSkill(float fCooldown);
	virtual ~SkulSkill() = default;

public:
	virtual void Awake() override { }
	virtual void Start() override { }
	virtual void Update() override { }
	virtual void LateUpdate() override { }
	virtual void FinalUpdate() override { }

public:
	FORCEINLINE SKUL_SKILL_POS GetSkillPos() { return m_eSkillPos; }
	FORCEINLINE void SetSkillPos(SKUL_SKILL_POS eSkillPos) { m_eSkillPos = eSkillPos; }

protected:
	SKUL_SKILL_POS m_eSkillPos;
	Timer m_tCooldown;
};

