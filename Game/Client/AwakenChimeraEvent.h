#pragma once
#include "DungeonEvent.h"
class Chimera;
class AwakenChimeraEvent :
    public DungeonEvent
{
public:
	AwakenChimeraEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<Chimera> pChimera);
	virtual ~AwakenChimeraEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	weak_ptr<Chimera> m_pChimera;
};

