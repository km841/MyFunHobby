#pragma once
#include "Skul.h"
class PlayerProjectile;
class LittleBone :
    public Skul
{
public:
	LittleBone();
	virtual ~LittleBone() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

public:
	FORCEINLINE bool HasHead()  { return m_eLittleBoneState == LITTLE_BONE_STATE::HAS_HEAD; }
	FORCEINLINE weak_ptr<PlayerProjectile> GetHeadProjectile() { return m_pHead; }
	void LoseHead();
	void PickUpHead();

public:
	virtual void CooldownCompletionCallback(SKILL_INDEX eSkillIndex) override;

private:
	void CreateHeadAndAddedToScene();
	

private:
	LITTLE_BONE_STATE m_eLittleBoneState;
	shared_ptr<PlayerProjectile> m_pHead;
};

