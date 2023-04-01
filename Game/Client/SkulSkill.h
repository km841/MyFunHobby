#pragma once
#include "GameObject.h"
class SkulSkill :
    public GameObject
{
public:
	explicit SkulSkill(float fCooldown, float fDuration);
	virtual ~SkulSkill() = default;

public:
	virtual void Awake() override { }
	virtual void Start() override { }
	virtual void Update() override { }
	virtual void LateUpdate() override { }
	virtual void FinalUpdate() override { }

public:
	FORCEINLINE SKILL_INDEX GetSkillIndex()						   { return m_eSkillIndex;        }
	FORCEINLINE void		SetSkillIndex(SKILL_INDEX eSkillIndex) { m_eSkillIndex = eSkillIndex; }

public:
	bool  IsActive()			{ return m_tCooldown.IsFinished();  }
	float GetCooldownProgress() { return m_tCooldown.GetProgress(); }

protected:
	SKILL_INDEX    m_eSkillIndex;
	Timer		   m_tCooldown;
	Timer		   m_tDuration;
};

