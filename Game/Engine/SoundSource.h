#pragma once
#include "Component.h"
class Sound;
class SoundSource :
    public Component
{
public:
	SoundSource();
	virtual ~SoundSource();

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	void Play();
	void Stop();
	void SetLoop(bool loop);
	void SetBGMClip(std::shared_ptr<Sound> clip);
	void PlayBGM();
	void StopBGM();

	void SetClip(std::shared_ptr<Sound> clip) { m_pSound = clip; }
	std::shared_ptr<Sound> GetClip() { return m_pSound; }

private:
	std::shared_ptr<Sound> m_pSound;
	std::shared_ptr<Sound> m_pBgmSound;
};

