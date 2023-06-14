#include "pch.h"
#include "EnableChapterBossHPBarTask.h"
#include "InterfaceManager.h"
#include "ChapterBossHPHUD.h"

EnableChapterBossHPBarTask::EnableChapterBossHPBarTask(shared_ptr<GameObject> pGameObject, STAGE_KIND eStageKind)
	: BehaviorTask(pGameObject)
	, m_eStageKind(eStageKind)
{
}

BEHAVIOR_RESULT EnableChapterBossHPBarTask::Run()
{
	static_pointer_cast<ChapterBossHPHUD>(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BOSS_HP))->SetStageKind(m_eStageKind);
	static_pointer_cast<ChapterBossHPHUD>(GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BOSS_HP))->Action();

	return BEHAVIOR_RESULT::SUCCESS;
}
