#include "MiniginPCH.h"
#include "MainMenu.h"
#include <iostream>
#include "InputManager.h"
#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include "Level.h"

MainMenu::MainMenu(const wstring& name)
	:Scene{ name }
	, m_StartP1ButtonPos{ 216.f,100.f }
	, m_StartP2ButtonPos{ 216.f,200.f }
	, m_QuitButtonPos{ 216.f,300.f }
	, m_LoadScene{ false }
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

	//start button 1P
	auto startButton = make_shared<minigin::GameObject>();
	startButton->SetTexture("Sprites/StartButtonOnePlayer.png");
	startButton->GetTransfrom()->SetPosition(m_StartP1ButtonPos.x, m_StartP1ButtonPos.y);
	m_StartButtonSize = startButton->GetTextureSize();

	Add(startButton);

	//start button 2P
	startButton = make_shared<minigin::GameObject>();
	startButton->SetTexture("Sprites/StartButtonTwoPlayer.png");
	startButton->GetTransfrom()->SetPosition(m_StartP2ButtonPos.x, m_StartP2ButtonPos.y);

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
	if (m_LoadScene)
	{
		m_LoadScene = false;
		minigin::SceneManager::GetInstance().SetActiveGameScene(minigin::SceneManager::GetInstance().GetScene(L"Level"));
	}
}

void MainMenu::Render() const
{}

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

	if (IsPointInRect(glm::vec2{ x,y }, m_StartP1ButtonPos, m_StartButtonSize.x, m_StartButtonSize.y))
	{
		Level::SetTwoPlayersSelected(false);
		m_LoadScene = true;
	}
	if (IsPointInRect(glm::vec2{ x,y }, m_StartP2ButtonPos, m_StartButtonSize.x, m_StartButtonSize.y))
	{
		Level::SetTwoPlayersSelected(true);
		m_LoadScene = true;
	}
	if (IsPointInRect(glm::vec2{ x,y }, m_QuitButtonPos, m_QuitButtonSize.x, m_QuitButtonSize.y)) minigin::Minigin::QuitProgram();
}

bool MainMenu::IsPointInRect(glm::vec2 point, glm::vec2 pos, float width, float height)
{
	return (point.x > pos.x&& point.x < pos.x + width && point.y > pos.y&& point.y < pos.y + height);
}

void ClickCommand::Execute()
{
	(m_Obj->*m_pFucntion)();
}
