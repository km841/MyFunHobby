#pragma once
class GameObject;
class Animation;
class SkulSkill
{
public:
	SkulSkill(float fCooldown, float fDuration);
	virtual ~SkulSkill() = default;

public:
	virtual void Update() = 0;
	virtual void CreateConditionFunction() = 0;

public:
	FORCEINLINE SKILL_INDEX			  GetSkillIndex()								   { return m_eSkillIndex;        }
	FORCEINLINE void				  SetSkillIndex(SKILL_INDEX eSkillIndex)		   { m_eSkillIndex = eSkillIndex; }
	FORCEINLINE const wstring&		  GetAnimationName()							   { return m_szAnimationName; }
	FORCEINLINE void				  SetAnimationName(const wstring& szAnimationName) { m_szAnimationName = szAnimationName; }
	FORCEINLINE weak_ptr<Animation>	  GetAnimation()								   { return m_pAnimation; }
	FORCEINLINE void				  SetAnimation(shared_ptr<Animation> pAnimation)   { m_pAnimation = pAnimation; }

	void Activate()									   { m_tDuration.Start(); }
	void DeActivate()								   { m_tCooldown.Start(); }
	bool IsCondition(weak_ptr<GameObject> pGameObject) { return m_fnCondition(pGameObject.lock()); }

public:
	bool  IsActive()			{ return m_tCooldown.IsFinished(); }
	bool  IsFinished()			{ return m_tDuration.IsFinished(); }
	float GetCooldownProgress() { return m_tCooldown.GetProgress(); }
	void  UpdateSkillCooldown();

protected:
	std::function<bool(weak_ptr<GameObject>)> m_fnCondition;
	shared_ptr<Animation>					  m_pAnimation;
	wstring									  m_szAnimationName;
	SKILL_INDEX								  m_eSkillIndex;
	Timer									  m_tCooldown;
	Timer									  m_tDuration;
};

