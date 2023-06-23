#include "pch.h"
#include "PlayBGMEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "Sound.h"
#include "SoundSource.h"
#include "ComponentObject.h"
#include "Resources.h"

PlayBGMEvent::PlayBGMEvent(shared_ptr<ConditionBlock> pConditionBlock, const wstring& szBgmPath)
	: DungeonEvent(DUNGEON_EVENT_KIND::MONSTER_SPAWN, pConditionBlock)
	, m_szBgmPath(szBgmPath)
{
}

PlayBGMEvent::~PlayBGMEvent()
{
}

void PlayBGMEvent::Update()
{
	DungeonEvent::Update();
}

void PlayBGMEvent::ExecuteEvent()
{
	SCENE_SOUND->SetBGMClip(GET_SINGLE(Resources)->Load<Sound>(m_szBgmPath, m_szBgmPath));
	SCENE_SOUND->PlayBGM();
}
