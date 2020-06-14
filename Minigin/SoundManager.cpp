#include "MiniginPCH.h"
#include "SoundManager.h"
#pragma warning(push)
#pragma warning(disable: 26812)
#pragma warning(pop)

minigin::SoundManager::SoundManager()
{
	Initialize();
}

minigin::SoundManager::~SoundManager()
{
	if (m_pFmodSystem)
	{
		m_pFmodSystem->release();
	}
}

bool minigin::SoundManager::ErrorCheck(FMOD_RESULT res)
{
	if (res != FMOD_OK)
	{
		wstringstream strstr;
		strstr << L"FMOD error! \n[" << res << L"] " << FMOD_ErrorString(res) << endl;
		Logger::LogError(strstr.str());
		return false;
	}
	return true;
}

void minigin::SoundManager::Initialize()
{
	unsigned int version;
	int numdrivers;
	/*
	Create a System object and initialize.
	*/
	FMOD_RESULT result = FMOD::System_Create(&m_pFmodSystem);
	ErrorCheck(result);
	result = m_pFmodSystem->getVersion(&version);
	ErrorCheck(result);

	if (version < FMOD_VERSION)
	{
		Logger::LogFormat(LogLevel::Error, L"SoundManager Initialization Failed!\n\nYou are using an old version of FMOD %08x. This program requires %08x\n",
			version, FMOD_VERSION);
		return;
	}

	result = m_pFmodSystem->getNumDrivers(&numdrivers);
	ErrorCheck(result);
	if (numdrivers == 0)
	{
		result = m_pFmodSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		ErrorCheck(result);
	}
	else
	{
		result = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr);
		ErrorCheck(result);
	}

}