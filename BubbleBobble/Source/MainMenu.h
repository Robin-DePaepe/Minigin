#pragma once
#include "Scene.h"
#include "Command.h"
#include <vector>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class MainMenu;

class ClickCommand final : public minigin::Command
{
public:
	ClickCommand(MainMenu* pObj, void(MainMenu::* pFucntion)())
		:Command{}
		, m_Obj{ pObj }
		, m_pFucntion{ pFucntion }
	{};

	virtual void Execute()  override;
	virtual void Undo() override {};
private:
	MainMenu* m_Obj;
	void(MainMenu::* m_pFucntion)();
};

class MainMenu final : public minigin::Scene
{
public:
	//rule of 5
	MainMenu(const wstring& name);
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

	void MouseButtonClicked();
	bool IsPointInRect(glm::vec2 point, glm::vec2 pos, float width, float height);
	//variables
	size_t m_ClickActionId;
	const glm::vec2 m_StartP1ButtonPos, m_StartP2ButtonPos, m_QuitButtonPos;
	glm::vec2 m_StartButtonSize, m_QuitButtonSize;
	bool m_LoadScene;

	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
};

