#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"
#include <SDL.h>
#include "TextObject.h"
#include <thread>

minigin::Scene::Scene(const wstring& name)
	: m_Name(name)
	, m_ShowFpsCounter{ false }
	, m_Processor_Cores{ thread::hardware_concurrency() }
{
	InitInput();

	//fps counter
	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	m_spFpsCounter = make_shared<TextObject>("INITIALIZING", fontFPS);

	m_spFpsCounter->SetColor({ 255,255,0 });
	m_spFpsCounter->SetPosition(150, 15);
}


void minigin::Scene::ShowFpsCounter(bool enable)
{
	m_ShowFpsCounter = enable;
}

const wstring& minigin::Scene::GetName() const
{
	return m_Name;
}

void minigin::Scene::HandleInput()
{
}

void minigin::Scene::InitInput()
{
}

void minigin::Scene::Add(const shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void minigin::Scene::RootUpdate()
{
	HandleInput();
	SoundManager::GetInstance().GetSystem()->update();

	if (m_ShowFpsCounter)
	{
		m_spFpsCounter->SetText(to_string(Time::GetInstance().GetFPS()) + "FPS");
		m_spFpsCounter->Update();
	}

	//multhi threat the updating of the objects in the scene
	vector<thread> pThreads;
	unsigned int counter{ 0 };

	for (auto& object : m_Objects)
	{
		thread pThread{ &SceneObject::Update, object };

		if (pThreads.size() == m_Processor_Cores)
		{
			pThreads[counter].join();

			++counter;
		}
		pThreads.push_back(move(pThread));
	}

	for (size_t i = counter; i < pThreads.size(); i++)
	{
		pThreads[i].join();
	}

	//delete objects
	auto it = m_Objects.begin();

	while (it != m_Objects.cend())
	{
		if ((*it)->Destroy())it = m_Objects.erase(it);
		else ++it;
	}
	Update();
}

void minigin::Scene::RootRender() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
	if (m_ShowFpsCounter) m_spFpsCounter->Render();

	Render();
}

