#pragma once
#include <string>
#include <SDL_mixer.h>
class SoundStream
{
public:
	explicit SoundStream(const std::string& path = "");
	~SoundStream();
	SoundStream& operator=(const SoundStream& rhs) = delete;
	SoundStream(const SoundStream& other) = delete;
	SoundStream(SoundStream&& other) = delete;
	SoundStream& operator=(SoundStream&& other) = delete;

	bool IsLoaded() const;
	bool Play(bool repeat) const;
	static void Stop();
	static void Pause();
	static void Resume();
	static void SetVolume(size_t value);
	static int GetVolume();
	static bool IsPlaying();

private:
	Mix_Music *m_pMixMusic;
};