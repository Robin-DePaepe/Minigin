#pragma once
#include "Singleton.h"

class SoundManager : public Singleton<SoundManager>
{
public:
	//rule of 5
	SoundManager();
	virtual ~SoundManager();

	SoundManager(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) noexcept = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager& operator=(SoundManager&& other) noexcept = delete;

	//public functions
	static bool ErrorCheck(FMOD_RESULT res);
	FMOD::System* GetSystem() const { return m_pFmodSystem; }

private:
	//datamembers
	FMOD::System* m_pFmodSystem = nullptr;
	//private functions
	void Initialize();
};


