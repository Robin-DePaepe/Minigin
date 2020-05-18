#pragma once
#include "SceneManager.h"
#include <string>

class TextObject;
class SceneObject;

class Scene 
{
public:
	//rule of 5
	explicit Scene(const std::wstring& name);
	virtual ~Scene() = default;

	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	//public functions
	virtual void Initialize() = 0;
	virtual void RootUpdate();
	virtual void RootRender() const;
	
	virtual void SceneActivated() {};
	virtual void SceneDeactivated() {};

	void Add(const std::shared_ptr<SceneObject>& object);

	void ShowFpsCounter(bool enable);
	const std::wstring& GetName() const;

private:
	//datamembers
	std::wstring m_Name;
	std::vector < std::shared_ptr<SceneObject>> m_Objects{};

	bool m_ShowFpsCounter;
	std::shared_ptr<TextObject> m_spFpsCounter;

	//private functions
	virtual void Update() = 0;
	virtual void Render() const = 0;
};


