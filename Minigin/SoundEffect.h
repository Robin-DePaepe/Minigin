#pragma once
#include <string>
#include <SDL_mixer.h>

class SoundEffect
{
public:
	explicit SoundEffect(const std::string& path);
	~SoundEffect();
	SoundEffect(const SoundEffect& other) = delete;
	SoundEffect& operator=(const SoundEffect& rhs) = delete;
	SoundEffect(SoundEffect&& other) = delete;
	SoundEffect& operator=(SoundEffect&& rhs) = delete;

	bool IsLoaded() const;
	bool Play(int loops) const;
	static void SetVolume(size_t value);
	static int GetVolume();
	static void StopAll();
	static void PauseAll();
	static void ResumeAll();

private:
	Mix_Chunk* m_pMixChunk;
};
