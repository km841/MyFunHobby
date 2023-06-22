#pragma once
class Sounds
{
	DECLARE_SINGLE(Sounds);
public:
	void Init();
	bool CreateSound(const std::string& path, FMOD::Sound** sound);
	void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
	void Set3DListenerAttributes(const Vec3* pos, const Vec3* vel, const Vec3* forward, const Vec3* up);
	void Release();

private:
	FMOD::Studio::System* mSystem;
	FMOD::System* mCoreSystem;
	
};

