#include "MiniginPCH.h"
#include "MainMenu.h"
#include <iostream>
#include "InputManager.h"
#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"

MainMenu::MainMenu(const wstring& name)
	:Scene{ name }
	,m_StartButtonPos{216.f,100.f}
	,m_QuitButtonPos{216.f,250.f}
{
}


void MainMenu::Initialize()
{
	//command
	shared_ptr<minigin::Command> clickCommand = make_shared<ClickCommand>(ClickCommand{ this, &MainMenu::MouseButtonClicked });
	m_ClickActionId = minigin::InputManager::GetInstance().AddInput(minigin::InputAction(clickCommand, true, VK_LBUTTON, minigin::ControllerButton::none, minigin::InputTriggerState::Pressed));

	//sound
	minigin::SoundManager::GetInstance().GetSystem()->createSound("Resources/Sounds/StartUpSound.wav", FMOD_2D, nullptr, &m_pSound);
	minigin::SoundManager::GetInstance().GetSystem()->playSound(m_pSound, 0, false, &m_pChannel);

	//start screen
	auto startScreen = make_shared<minigin::GameObject>();
	startScreen->SetTexture("Sprites/StartScreen.png");

	Add(startScreen);

	//start button
	auto startButton = make_shared<minigin::GameObject>();
	startButton->SetTexture("Sprites/StartButton.png");
	startButton->GetTransfrom()->SetPosition(m_StartButtonPos.x,m_StartButtonPos.y);
	m_StartButtonSize = startButton->GetTextureSize();

	Add(startButton);

	//quit button
	auto quitButton = make_shared<minigin::GameObject>();
	quitButton->SetTexture("Sprites/Quit.png");
	quitButton->GetTransfrom()->SetPosition(m_QuitButtonPos.x, m_QuitButtonPos.y);
	m_QuitButtonSize = quitButton->GetTextureSize();

	Add(quitButton);
}

void MainMenu::Update()
{
}

void MainMenu::Render() const
{
}

void MainMenu::SceneActivated()
{
	minigin::SoundManager::GetInstance().GetSystem()->playSound(m_pSound, 0, false, &m_pChannel);
	minigin::InputManager::GetInstance().ChangeInputActionStatus(m_ClickActionId, true);

	for (const auto& object : m_Objects) 
	{
		shared_ptr<minigin::GameObject> pGameObject{ dynamic_pointer_cast<minigin::GameObject>(object) };

		if (pGameObject != nullptr)  pGameObject->SetActions(true);
	}
}

void MainMenu::SceneDeactivated()
{
	m_pChannel->setPaused(true);

	minigin::InputManager::GetInstance().ChangeInputActionStatus(m_ClickActionId, false);

	for (const auto& object : m_Objects)
	{
		shared_ptr<minigin::GameObject> pGameObject{ dynamic_pointer_cast<minigin::GameObject>(object) };

		if (pGameObject != nullptr)  pGameObject->SetActions(false);
	}
}

void MainMenu::MouseButtonClicked()
{
	int x{}, y{};
	minigin::InputManager::GetInstance().GetMousePos(x, y);

	if (IsPointInRect(glm::vec2{ x,y }, m_StartButtonPos, m_StartButtonSize.x, m_StartButtonSize.y)) minigin::SceneManager::GetInstance().SetActiveGameScene(minigin::SceneManager::GetInstance().GetScene(L"Level1"));
	if (IsPointInRect(glm::vec2{x,y},m_QuitButtonPos, m_QuitButtonSize.x, m_QuitButtonSize.y)) minigin::Minigin::QuitProgram();
}

bool MainMenu::IsPointInRect(glm::vec2 point, glm::vec2 pos, float width, float height)
{
	return (
		point.x > pos.x && point.x < pos.x + width &&
		point.y > pos.y && point.y < pos.y + height
		);
}

void ClickCommand::Execute()
{
	(m_Obj->*m_pFucntion)();
}
