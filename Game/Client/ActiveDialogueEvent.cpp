#include "pch.h"
#include "ActiveDialogueEvent.h"
#include "DialogueUI.h"
#include "InterfaceManager.h"

ActiveDialogueEvent::ActiveDialogueEvent(shared_ptr<ConditionBlock> pConditionBlock, const wstring& szTalker, const wstring& szLine, float fDuration)
	: DungeonEvent(DUNGEON_EVENT_KIND::ACTIVE_DIALOGUE, pConditionBlock)
	, m_szTalker(szTalker)
	, m_szLine(szLine)
	, m_fDuration(fDuration)
{
}

ActiveDialogueEvent::~ActiveDialogueEvent()
{
}

void ActiveDialogueEvent::Update()
{
	DungeonEvent::Update();
}

void ActiveDialogueEvent::ExecuteEvent()
{
	static_pointer_cast<DialogueUI>(GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE))->SetTalkerAndLine(m_szTalker, m_szLine, m_fDuration);
	static_pointer_cast<DialogueUI>(GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE))->Action();
}
