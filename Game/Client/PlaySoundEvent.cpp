#include "pch.h"
#include "PlaySoundEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "Sound.h"
#include "SoundSource.h"
#include "ComponentObject.h"
#include "Resources.h"

PlaySoundEvent::PlaySoundEvent(shared_ptr<ConditionBlock> pConditionBlock, const wstring& szSoundPath)
	: DungeonEvent(DUNGEON_EVENT_KIND::PLAY_SOUND, pConditionBlock)
	, m_szSoundPath(szSoundPath)
{
}

PlaySoundEvent::~PlaySoundEvent()
{
}

void PlaySoundEvent::Update()
{
	DungeonEvent::Update();
}

void PlaySoundEvent::ExecuteEvent()
{
	SCENE_SOUND->SetClip(GET_SINGLE(Resources)->Load<Sound>(m_szSoundPath, m_szSoundPath));
	SCENE_SOUND->Play();
}
