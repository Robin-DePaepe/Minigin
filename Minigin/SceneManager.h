#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace minigin
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager() = default;
		 ~SceneManager() = default;

		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;

		//functions
		void Update();
		void Render();

		void AddGameScene(shared_ptr<Scene> spScene);

		void RemoveGameScene(shared_ptr<Scene> spScene);
		void RemoveGameScene(const wstring& sceneName);

		void SetActiveGameScene(const wstring& sceneName);
		void SetActiveGameScene(shared_ptr<Scene> spScene);

		void NextScene();
		void PreviousScene();

		shared_ptr<Scene> GetActiveScene() const { return m_spActiveScene; }
		shared_ptr<Scene> GetScene(const wstring& sceneName) const;

	private:
		friend class Singleton<SceneManager>;
		//datamembers
		vector<shared_ptr<Scene>> m_spScenes;
		shared_ptr<Scene> m_spActiveScene;
	};
}
