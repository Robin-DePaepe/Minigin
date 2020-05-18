#pragma once
#include "Scene.h"

class TestScene1 final : public Scene
{
public:
	//rule of 5
	TestScene1(const std::wstring& name);
	~TestScene1() = default;

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

};

