#pragma once
#include "Scene.h"
#include "Command.h"
#include "State.h"
#include "TestStatesManager.h"


class TestCommand : public Command
{
public:
	TestCommand(TestStatesManager* pObj, void(TestStatesManager::*pFucntion)())
		:Command{}
		,m_Obj{pObj}
		,m_pFucntion{pFucntion}
	{};

	virtual void Execute()  override;
	virtual void Undo() override {};
private:
	TestStatesManager* m_Obj;
	void(TestStatesManager::* m_pFucntion)();
};

class TestScene1 final : public Scene
{
public:
	//rule of 5
	TestScene1(const std::wstring& name);
	~TestScene1();

	TestScene1(const TestScene1& other) = delete;
	TestScene1(TestScene1&& other) = delete;
	TestScene1& operator=(const TestScene1& other) = delete;
	TestScene1& operator=(TestScene1&& other) = delete;

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;

	virtual void SceneActivated() override;
	virtual void SceneDeactivated() override;

	//
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
	TestStatesManager* m_pTestStateManager;
};

