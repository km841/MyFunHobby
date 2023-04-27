#include "pch.h"
#include "PlayerFunctionScript.h"
#include "Player.h"
#include "Skul.h"
#include "SkulSkill.h"
#include "PlayerState.h"
#include "Input.h"
#include "InterfaceManager.h"
#include "UI.h"
#include "EventManager.h"
#include "PauseEvent.h"
#include "PlayEvent.h"

PlayerFunctionScript::PlayerFunctionScript()
{
}

PlayerFunctionScript::~PlayerFunctionScript()
{
}

void PlayerFunctionScript::LateUpdate()
{
	shared_ptr<Player> pPlayer = static_pointer_cast<Player>(GetGameObject());

	if (IS_DOWN(KEY_TYPE::A))
	{
		weak_ptr<SkulSkill> pFirstSkill = pPlayer->GetActiveSkul()->GetSkill(SKILL_INDEX::FIRST).lock();
		if (pFirstSkill.lock() &&
			pFirstSkill.lock()->IsActive() &&
			pFirstSkill.lock()->IsCondition(pPlayer->GetActiveSkul()))
		{
			pPlayer->GetActiveSkul()->SetActiveSkill(SKILL_INDEX::FIRST);
			pPlayer->GetActiveSkul()->EnableSkillActiveFlag(pFirstSkill.lock()->GetSkillType());
		}
	}

	if (IS_DOWN(KEY_TYPE::S))
	{
		weak_ptr<SkulSkill> pSecondSkill = pPlayer->GetActiveSkul()->GetSkill(SKILL_INDEX::SECOND).lock();
		if (pSecondSkill.lock() &&
			pSecondSkill.lock()->IsActive() &&
			pSecondSkill.lock()->IsCondition(pPlayer->GetActiveSkul()))
		{
			pPlayer->GetActiveSkul()->SetActiveSkill(SKILL_INDEX::SECOND);
			pPlayer->GetActiveSkul()->EnableSkillActiveFlag(pSecondSkill.lock()->GetSkillType());
		}
	}

	if (IS_DOWN(KEY_TYPE::SPACE))
	{
		if (pPlayer->IsSwapPossible())
			pPlayer->EnableSwapActiveFlag();
	}

	if (IS_DOWN(KEY_TYPE::TAB))
	{
		GET_SINGLE(InterfaceManager)->Get(UI_TYPE::INVENTORY)->FlipState();
		if (GET_SINGLE(InterfaceManager)->Get(UI_TYPE::INVENTORY)->IsEnable())
			GET_SINGLE(EventManager)->AddEvent(make_unique<PauseEvent>());
		else
			GET_SINGLE(EventManager)->AddEvent(make_unique<PlayEvent>());
	}
}
