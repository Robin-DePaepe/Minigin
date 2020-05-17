#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"
#include <SDL.h>
#include "TextObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name(name) 
	,m_ShowFpsCounter{false}
{
	//fps counter
	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	m_spFpsCounter = std::make_shared<TextObject>( "INITIALIZING", fontFPS );

	m_spFpsCounter->SetColor({ 255,255,0 });
	m_spFpsCounter->SetPosition(15, 15);
}

Scene::~Scene() = default;


void Scene::ShowFpsCounter(bool enable)
{
	m_ShowFpsCounter = enable;
}

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
	if (m_ShowFpsCounter)
	{
		m_spFpsCounter->SetText(std::to_string(Time::GetInstance().GetFPS()) + "FPS");
		m_spFpsCounter->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
	if (m_ShowFpsCounter) m_spFpsCounter->Render();
}
