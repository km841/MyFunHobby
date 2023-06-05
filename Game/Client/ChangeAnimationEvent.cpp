#include "pch.h"
#include "ChangeAnimationEvent.h"
#include "Animator.h"
#include "GameObject.h"

ChangeAnimationEvent::ChangeAnimationEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<GameObject> pGameObject, const wstring& szAnimName, bool bLoop, int32 iSection)
	: DungeonEvent(DUNGEON_EVENT_KIND::CHANGE_ANIMATION, pConditionBlock)
	, m_pGameObject(pGameObject)
	, m_szAnimName(szAnimName)
	, m_bLoop(bLoop)
	, m_iSection(iSection)
{
}

ChangeAnimationEvent::~ChangeAnimationEvent()
{
}

void ChangeAnimationEvent::Update()
{
	DungeonEvent::Update();
}

void ChangeAnimationEvent::ExecuteEvent()
{
	assert(m_pGameObject.lock()->GetAnimator());
	m_pGameObject.lock()->GetAnimator()->Play(m_szAnimName, m_bLoop, m_iSection);
}
