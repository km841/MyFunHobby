#include "pch.h"
#include "PlaySoundTask.h"
#include "Scenes.h"
#include "Scene.h"
#include "Sound.h"
#include "SoundSource.h"
#include "ComponentObject.h"
#include "Resources.h"

PlaySoundTask::PlaySoundTask(shared_ptr<GameObject> pGameObject, const wstring& szSoundPath)
	: BehaviorTask(pGameObject)
	, m_szSoundPath(szSoundPath)
{
}

BEHAVIOR_RESULT PlaySoundTask::Run()
{
	shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(m_szSoundPath, m_szSoundPath);
	SCENE_SOUND->SetClip(pSound);
	SCENE_SOUND->Play();
	
	return BEHAVIOR_RESULT::SUCCESS;
}
