#include "pch.h"
#include "SkulSkill.h"
#include "Clock.h"

SkulSkill::SkulSkill(const SkillInfo& skillInfo)
	: m_eSkillIndex(SKILL_INDEX::END)
	, m_SkillInfo(skillInfo)
	, m_tCooldown(skillInfo.fCooldown)
	, m_tDuration(skillInfo.fDuration)
	, m_fMaxChargingTime(0.f)
	, m_fChargingProgress(0.f)
{
}

void SkulSkill::Update()
{
	m_tDuration.Update(DELTA_TIME);
}


void SkulSkill::UpdateSkillCooldown()
{
	m_tCooldown.Update(DELTA_TIME);
}


