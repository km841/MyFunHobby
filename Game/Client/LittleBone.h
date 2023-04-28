#pragma once
#include "Skul.h"

class GlobalEffect;
class LittleBoneHead;
class LittleBone :
    public Skul
{
public:
	LittleBone(const SkulInfo& skulInfo);
	virtual ~LittleBone() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

public:
	FORCEINLINE bool HasHead()  { return m_eLittleBoneState == LITTLE_BONE_STATE::HAS_HEAD; }
	FORCEINLINE weak_ptr<LittleBoneHead> GetHeadProjectile() { return m_pHead; }
	void LoseHead();
	void PickUpHead();

public:
	virtual void CooldownCompletionCallback(SKILL_INDEX eSkillIndex) override;

private:
	void CreateHeadAndAddedToScene();
	

private:
	LITTLE_BONE_STATE m_eLittleBoneState;
	shared_ptr<LittleBoneHead> m_pHead;
	
};

