#pragma once
#include "DungeonEvent.h"
class SceneChangeDungeonEvent :
    public DungeonEvent
{
public:
	SceneChangeDungeonEvent(shared_ptr<ConditionBlock> pConditionBlock, SCENE_TYPE eSceneType);
	virtual ~SceneChangeDungeonEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	SCENE_TYPE m_eSceneType;
};

