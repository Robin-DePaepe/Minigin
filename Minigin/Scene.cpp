#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"
#include <SDL.h>
#include "TextObject.h"


Scene::Scene(const std::wstring& name)
	: m_Name(name) 
	,m_ShowFpsCounter{false}
{
	InitInput();

	//fps counter
	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	m_spFpsCounter = std::make_shared<TextObject>( "INITIALIZING", fontFPS );

	m_spFpsCounter->SetColor({ 255,255,0 });
	m_spFpsCounter->SetPosition(15, 15);
}


void Scene::ShowFpsCounter(bool enable)
{
	m_ShowFpsCounter = enable;
}

const std::wstring& Scene::GetName() const
{
	return m_Name;
}

void Scene::HandleInput()
{
}

void Scene::InitInput()
{
}

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::RootUpdate()
{
	HandleInput();

	for(auto& object : m_Objects)
	{
		object->Update();
	}
	if (m_ShowFpsCounter)
	{
		m_spFpsCounter->SetText(std::to_string(Time::GetInstance().GetFPS()) + "FPS");
		m_spFpsCounter->Update();
	}
	Update();
}

void Scene::RootRender() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
	if (m_ShowFpsCounter) m_spFpsCounter->Render();

	Render();
}

