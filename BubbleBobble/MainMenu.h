#pragma once
#include "Scene.h"

class MainMenu final : public Scene
{
public:
	//rule of 5
	MainMenu(const std::wstring& name);
	~MainMenu() = default;

	MainMenu(const MainMenu& other) = delete;
	MainMenu(MainMenu&& other) = delete;
	MainMenu& operator=(const MainMenu& other) = delete;
	MainMenu& operator=(MainMenu&& other) = delete;

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;

	virtual void SceneActivated() override;
	virtual void SceneDeactivated() override;
};

