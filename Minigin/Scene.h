#pragma once
#include "SceneManager.h"
#include <string>

class TextObject;
class SceneObject;

class Scene 
{
public:
	//rule of 5
	explicit Scene(const wstring& name);
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

	void Add(const shared_ptr<SceneObject>& object);

	void ShowFpsCounter(bool enable);
	const wstring& GetName() const;

private:
	//datamembers
	wstring m_Name;
	vector < shared_ptr<SceneObject>> m_Objects{};

	bool m_ShowFpsCounter;
	shared_ptr<TextObject> m_spFpsCounter;

	const unsigned int m_Processor_Cores;
	//private functions
	virtual void Update() = 0;
	virtual void Render() const = 0;

	void HandleInput();
	void InitInput();
};


