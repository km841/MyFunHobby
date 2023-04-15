#pragma once
#include "GameObject.h"

class SkulAttack;
class SkulSkill;
class Animation;
class Player;
class Texture;
class Skul :
	public GameObject
{
public:
	explicit Skul(SKUL_GRADE eSkulGrade);
	virtual ~Skul() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

public:
	FORCEINLINE SKUL_INDEX			 GetSkulIndex()										   { return m_eSkulIndex;     }
	FORCEINLINE SKUL_GRADE			 GetSkulGrade()										   { return m_eSkulGrade;   }
	FORCEINLINE void				 SetSkulIndex(SKUL_INDEX eSkulIndex)				   { m_eSkulIndex = eSkulIndex; }
	FORCEINLINE bool				 IsSkillActiveFlag()								   { return SKILL_TYPE::NONE != m_bSkillActiveType; }
	FORCEINLINE SKILL_TYPE			 GetSkillActiveType()								   { return m_bSkillActiveType; }
	FORCEINLINE weak_ptr<SkulSkill>  GetActiveSkill()									   { return m_pActiveSkill; }
	FORCEINLINE weak_ptr<SkulSkill>  GetSwapSkill()										   { return m_pSwapSkill; }
	FORCEINLINE weak_ptr<SkulSkill>  GetSkill(SKILL_INDEX eSkillIndex)					   { return m_arrSkills[static_cast<uint8>(eSkillIndex)]; }
	FORCEINLINE weak_ptr<Player>	 GetPlayer()										   { return m_pPlayer.lock(); }
	FORCEINLINE weak_ptr<Texture>	 GetThumnailImage()									   { return m_pThumnailImage; }
	FORCEINLINE void			     SetThumnailImage(shared_ptr<Texture> pTexture)		   { m_pThumnailImage = pTexture; }
	FORCEINLINE void				 DisableSkillActiveFlag()							   { m_bSkillActiveType = SKILL_TYPE::NONE; }
	FORCEINLINE void				 EnableSkillActiveFlag(SKILL_TYPE eSkillType)		   { m_bSkillActiveType = eSkillType; }
	FORCEINLINE weak_ptr<SkulAttack> GetAttackMethod()									   { return m_pAttackMethod; }
	

public:
	weak_ptr<Animation>				GetActiveAnimation();
	
	void							SetActiveSkill(SKILL_INDEX eSkillIndex);
	void							SetPlayer(shared_ptr<Player> pPlayer);
	void							ObtainSkill(shared_ptr<SkulSkill> pSkulSkill);
	void							SetSwapSkill(shared_ptr<SkulSkill> pSkulSkill);
	void							SkillCooldownUpdate();
	void							RefreshAnimation();
	void							SetAttackMethod(shared_ptr<SkulAttack> pAttackMethod);

public:
	void							CooldownCompletion(SKILL_INDEX eSkillIndex);
	virtual void					CooldownCompletionCallback(SKILL_INDEX eSkillIndex) { }

public:
	// Helper Functions
	void AddAnimation(PLAYER_STATE ePlayerState, const wstring& szName, shared_ptr<Animation> pAnimation, uint8 iEnum = 0);
	void AddAttackAnimation(ATTACK_ORDER eAttackOrder, const wstring& szName, shared_ptr<Animation> pAnimation, uint8 iEnum = 0);
	void PlayAnimation(const wstring& szName, bool bLoop = true, int32 iSection = 0);
	void PlayAnimation(PLAYER_STATE ePlayerState, bool bLoop = true, int32 iSection = 0);
	void PlayAnimation(ATTACK_ORDER eAttackOrder, bool bLoop = true, int32 iSection = 0);

private:
	const wstring& GetStateToName(PLAYER_STATE ePlayerState);
	
public:
	FORCEINLINE void    SetEnumIndex(uint8 iEnumIndex) { m_iEnumIndex = iEnumIndex; }
	FORCEINLINE uint8	GetEnumIndex()				   { return m_iEnumIndex; }

protected:
	weak_ptr<Player>								   m_pPlayer;

	// About Enums
	SKUL_GRADE										   m_eSkulGrade;
	SKUL_INDEX										   m_eSkulIndex;
	uint8											   m_iEnumIndex;

	// About Skill
	std::array<shared_ptr<SkulSkill>, MAX_SKILLS>	   m_arrSkills;
	SKILL_TYPE										   m_bSkillActiveType;
	weak_ptr<SkulSkill>								   m_pActiveSkill;
	shared_ptr<SkulSkill>							   m_pSwapSkill;

	// About Attack
	shared_ptr<SkulAttack>							   m_pAttackMethod;
	
	std::vector<std::map<PLAYER_STATE, wstring>>	   m_vStateToNameMaps;
	
	shared_ptr<Texture>								   m_pThumnailImage;
};

