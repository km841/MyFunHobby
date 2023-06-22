#pragma once
#include "SkulSkill.h"
class LocalEffect;
class RageTackleSkill :
    public SkulSkill
{
public:
	RageTackleSkill(const SkillInfo& skillInfo);
	virtual ~RageTackleSkill() = default;

public:
	virtual void Update() override;
	virtual void CreateConditionFunction() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	void CreateSlashEffectAndAddedToScene();
	void CreateFlashEffectAndAddedToScene();

private:
	weak_ptr<LocalEffect> m_pFlashEffect;
	float m_fDepthValue;

	Timer m_tSlashTick;
};

