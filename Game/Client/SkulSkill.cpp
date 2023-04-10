#include "pch.h"
#include "SkulSkill.h"
#include "Clock.h"

SkulSkill::SkulSkill(SKILL_TYPE eSkillType, float fCooldown, float fDuration)
	: m_eSkillIndex(SKILL_INDEX::END)
	, m_eSkillType(eSkillType)
	, m_tCooldown(fCooldown)
	, m_tDuration(fDuration)
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


