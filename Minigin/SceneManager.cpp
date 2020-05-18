#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update()
{
	m_spActiveScene->RootUpdate();
}

void SceneManager::Render()
{
	m_spActiveScene->RootRender();
}

void SceneManager::AddGameScene(shared_ptr<Scene> spScene)
{
	if (spScene == nullptr)
	{
		Logger::LogError(L"Attempt to add invalid scene (AddGameScene)", true);
		return;
	}


	//check if the name isn't already used
	for (const auto& scene : m_spScenes)
	{
		if (scene->GetName() == spScene->GetName()) return; //throw warning
	}
	m_spScenes.push_back(spScene);
	spScene->Initialize();

	if (m_spScenes.size() == 1) SetActiveGameScene(spScene);
}

void SceneManager::RemoveGameScene(shared_ptr<Scene> spScene)
{
	if (spScene == nullptr)
	{
		Logger::LogWarning(L"Scene is not found (RemoveGameScene)", true);
		return;
	}


	//remove the scene from the vector
	auto it = find(m_spScenes.cbegin(), m_spScenes.cend(), spScene);

	if (it != m_spScenes.end()) m_spScenes.erase(it);
}

void SceneManager::RemoveGameScene(const wstring& sceneName)
{
	RemoveGameScene(GetScene(sceneName));
}

void SceneManager::SetActiveGameScene(const wstring& sceneName)
{
	SetActiveGameScene(GetScene(sceneName));
}

void SceneManager::SetActiveGameScene(shared_ptr<Scene> spScene)
{
	if (spScene == nullptr)
	{
		Logger::LogError(L"Attempt to select an invalid scene (SetActiveGameScene)", true);
		return;
	}
	if (m_spActiveScene != nullptr) m_spActiveScene->SceneDeactivated();

	m_spActiveScene = spScene;

	m_spActiveScene->SceneActivated();
}

void SceneManager::NextScene()
{
	auto it = find(m_spScenes.cbegin(), m_spScenes.cend(), m_spActiveScene);

	++it;

	if (it == m_spScenes.cend()) it = m_spScenes.cbegin();

	SetActiveGameScene(*it);
}

void SceneManager::PreviousScene()
{
	auto it = find(m_spScenes.cbegin(), m_spScenes.cend(), m_spActiveScene);

	if (it == m_spScenes.cbegin()) it = m_spScenes.cend();

	--it;

	SetActiveGameScene(*it);
}

shared_ptr<Scene> SceneManager::GetScene(const wstring& sceneName)
{
	for (const auto& scene : m_spScenes)
	{
		if (scene->GetName() == sceneName)
		{
			return scene;
		}
	}
	Logger::LogWarning(L"Scene not found (GetScene)", true);
	return nullptr;
}

