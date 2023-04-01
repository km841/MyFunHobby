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
	FORCEINLINE SKUL_POS   GetSkulPos()					   { return m_eSkulPos; }
	FORCEINLINE void	   SetSkulPos(SKUL_POS eSkulPos)   { m_eSkulPos = eSkulPos; }
	FORCEINLINE SKUL_GRADE GetSkulGrade()				   { return m_eSkulGrade; }
	void SetPlayer(shared_ptr<Player> pPlayer);
	shared_ptr<Animation> GetActiveAnimation();

public:
	// Helper Functions
	void AddAnimation(PLAYER_STATE ePlayerState, const wstring& szName, shared_ptr<Animation> pAnimation);
	void PlayAnimation(PLAYER_STATE ePlayerState, bool bLoop = true, int32 iSection = 0);
	

private:
	const wstring& GetStateToName(PLAYER_STATE ePlayerState);

protected:
	weak_ptr<Player>								   m_pPlayer;
	SKUL_GRADE										   m_eSkulGrade;
	SKUL_POS										   m_eSkulPos;
	std::map<PLAYER_STATE, wstring>					   m_mStateToNameMap;
	std::array<shared_ptr<SkulSkill>, SKUL_MAX_SKILLS> m_arrSkills;
};

