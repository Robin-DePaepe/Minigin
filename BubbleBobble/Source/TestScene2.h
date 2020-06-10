#pragma once
#include "Scene.h"

class ITextLocalizer;

class TestScene2 final: public Scene
{
public:
	//rule of 5
	 TestScene2(const std::wstring& name);
	 ~TestScene2() = default;

	TestScene2(const TestScene2& other) = delete;
	TestScene2(TestScene2&& other) = delete;
	TestScene2& operator=(const TestScene2& other) = delete;
	TestScene2& operator=(TestScene2&& other) = delete;

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;

	virtual void SceneActivated() override;
	virtual void SceneDeactivated() override;
	void TestLoca(ITextLocalizer* localizer);

	ITextLocalizer* localizer;

};

