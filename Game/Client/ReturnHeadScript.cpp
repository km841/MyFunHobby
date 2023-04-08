#include "pch.h"
#include "ReturnHeadScript.h"
#include "LittleBone.h"
#include "Clock.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "SkullThrowSkill.h"

ReturnHeadScript::ReturnHeadScript(weak_ptr<LittleBone> pLittleBone)
	: m_pLittleBone(pLittleBone)
{
}

ReturnHeadScript::~ReturnHeadScript()
{
}

void ReturnHeadScript::LateUpdate()
{
	float fProgress = m_pLittleBone.lock()->GetSkill(SKILL_INDEX::FIRST).lock()->GetCooldownProgress();
	if (m_pLittleBone.lock()->GetSkill(SKILL_INDEX::FIRST).lock()->IsActive())
	{
		m_pLittleBone.lock()->PickUpHead();
	}
	else
	{
		m_pLittleBone.lock()->LoseHead();
	}
}
