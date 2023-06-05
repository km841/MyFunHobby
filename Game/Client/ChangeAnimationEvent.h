#pragma once
#include "DungeonEvent.h"
class GameObject;
class ChangeAnimationEvent :
    public DungeonEvent
{
public:
	ChangeAnimationEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<GameObject> pGameObject, const wstring& szAnimName, bool bLoop = true, int32 iSection = 0);
	virtual ~ChangeAnimationEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	weak_ptr<GameObject> m_pGameObject;
	wstring m_szAnimName;
	bool m_bLoop;
	int32 m_iSection;
};

