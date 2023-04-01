#pragma once
#include "GameObject.h"

class SkulSkill;
class Animation;
class Player;
class Skul :
	public GameObject
{
public:
	explicit Skul(SKUL_GRADE eSkulGrade);
	virtual ~Skul() = default;

public:
	virtual void Awake() override { }
	virtual void Start() override { }
	virtual void Update() override { }
	virtual void LateUpdate() override { }
	virtual void FinalUpdate() override { }

public:
	FORCEINLINE SKUL_INDEX			GetSkulIndex()				           { return m_eSkulIndex;     }
	FORCEINLINE void				SetSkulIndex(SKUL_INDEX eSkulIndex)    { m_eSkulIndex = eSkulIndex; }
	FORCEINLINE SKUL_GRADE			GetSkulGrade()						   { return m_eSkulGrade;   }
	FORCEINLINE bool				IsSkillActiveFlag()					   { return m_bSkillActiveFlag; }
	FORCEINLINE void				DisableSkillActiveFlag()			   { m_bSkillActiveFlag = false; }
	FORCEINLINE void				EnableSkillActiveFlag()				   { m_bSkillActiveFlag = true; }
	FORCEINLINE weak_ptr<SkulSkill> GetActiveSkill()					   { return m_pActiveSkill; }
	FORCEINLINE weak_ptr<SkulSkill> GetSkill(SKILL_INDEX eSkillIndex)	   { return m_arrSkills[static_cast<uint8>(eSkillIndex)]; }
	shared_ptr<Animation> GetActiveAnimation();
	void SetPlayer(shared_ptr<Player> pPlayer);
	void SetActiveSkill(SKILL_INDEX eSkillIndex);

public:
	// Helper Functions
	void AddAnimation(PLAYER_STATE ePlayerState, const wstring& szName, shared_ptr<Animation> pAnimation);
	void PlayAnimation(PLAYER_STATE ePlayerState, bool bLoop = true, int32 iSection = 0);
	
private:
	const wstring& GetStateToName(PLAYER_STATE ePlayerState);

protected:
	bool											   m_bSkillActiveFlag;
	weak_ptr<Player>								   m_pPlayer;
	SKUL_GRADE										   m_eSkulGrade;
	SKUL_INDEX										   m_eSkulIndex;

	weak_ptr<SkulSkill>								   m_pActiveSkill;
	std::map<PLAYER_STATE, wstring>					   m_mStateToNameMap;
	std::array<shared_ptr<SkulSkill>, MAX_SKILLS>	   m_arrSkills;
};

