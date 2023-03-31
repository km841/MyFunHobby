#pragma once
#include "GameObject.h"

class SkulSkill;
class Animation;
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
	FORCEINLINE SKUL_POS   GetSkulPos()				     { return m_eSkulPos; }
	FORCEINLINE void	   SetSkulPos(SKUL_POS eSkulPos) { m_eSkulPos = eSkulPos; }
	FORCEINLINE SKUL_GRADE GetSkulGrade()				 { return m_eSkulGrade; }

	void AddAnimation(PLAYER_STATE ePlayerState, const wstring& szName, shared_ptr<Animation> pAnimation);
	const wstring& GetStateToKey(PLAYER_STATE ePlayerState);

protected:
	SKUL_GRADE m_eSkulGrade;
	SKUL_POS   m_eSkulPos;
	std::map<PLAYER_STATE, wstring>	m_mStateToKeyMap;
	std::array<shared_ptr<SkulSkill>, SKUL_MAX_SKILLS> m_arrSkills;
	// 2번째 스킬은 유니크 등급 이상만 사용할 수 있다.

};

