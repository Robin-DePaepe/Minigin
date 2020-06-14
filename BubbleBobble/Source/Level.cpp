#include "Level.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Minigin.h"
#include "BoxCollider.h"
#include <RigidBodyComponent.h>
#include "ZenChan.h"

using namespace minigin;

bool Level::m_TwoPlayersSelected = false;
unsigned int Level::m_LevelNumber = 6;

Level::Level(const wstring& name)
	:Scene{ name }
{
	LevelParser levelParser;

	m_Levels = move(levelParser.Parse("SeperatedLevelData.dat"));
}

void Level::Initialize()
{}

void Level::Update()
{
	bool enemies{ false };

	for (const auto& object : m_Objects)
	{		
		auto gameObj = dynamic_pointer_cast<GameObject>(object);

		if (gameObj != nullptr)
		{
			if (gameObj->GetName() == L"Enemy") enemies = true;
			auto object{ gameObj->GetNewObject() };
			if(object != nullptr) Add(object);
		}
	}
	//p1
	auto bubble{ m_spPlayer1->GetBubble() };
	if (bubble != nullptr) Add(bubble);

	//p2
	if (m_TwoPlayersSelected)
	{
		bubble = m_spPlayer2->GetBubble();
		if (bubble != nullptr) Add(bubble);
	}

	if (enemies == false) SceneManager::GetInstance().NextScene();
}

void Level::Render() const
{
}

void Level::SceneActivated()
{
	std::cout << "Player1 controls:  A = left,  D = right,  W = jump, E = Fire \n";
	std::cout << "Player1 controls controller:  dpadLeft = left,  dpadRight = right,  dpadUp = jump, leftTrigger = Fire \n \n";

	m_spPlayer1 = make_shared<Player>(glm::vec2{ 150.f,100.f }, 'A', minigin::ControllerButton::DpadLeft, 'D', minigin::ControllerButton::DpadRight,
		'W', minigin::ControllerButton::DpadUp, 'E', minigin::ControllerButton::LeftTrigger);
	m_spPlayerGameObject1 = m_spPlayer1;
	Add(m_spPlayerGameObject1);

	if (m_TwoPlayersSelected)
	{
		std::cout << "Player2 controls:  left arrow = left,  right arrow = right,  up arrow = jump, down arrow = Fire \n";
		std::cout << "Player2 controls controller:  X = left,  B = right,  A = jump, rightTrigger = Fire \n \n";

		m_spPlayer2 = make_shared<Player>(glm::vec2{ 550.f,100.f }, VK_LEFT, minigin::ControllerButton::ButtonX, VK_RIGHT, minigin::ControllerButton::ButtonB,
			VK_UP, minigin::ControllerButton::ButtonA, VK_DOWN, minigin::ControllerButton::RightTrigger);
		m_spPlayerGameObject2 = m_spPlayer2;
		Add(m_spPlayerGameObject2);
	}

	Add(make_shared<ZenChan>(glm::vec2{100.f,300.f}));
	Add(make_shared<ZenChan>(glm::vec2{400.f,150.f}));
	Add(make_shared<ZenChan>(glm::vec2{300.f,400.f}));

	LoadLevel();
}

void Level::SceneDeactivated()
{
	cout << "\nPlayer 1 had a score of : " << m_spPlayer1->GetScore() << std::endl;
	if (m_TwoPlayersSelected) cout << "\nPlayer 2 had a score of : " << m_spPlayer2->GetScore() << std::endl;

	m_spPlayer1 = nullptr;
	m_spPlayer2 = nullptr;

	m_spPlayerGameObject1->Destroy();
	if (m_spPlayerGameObject2 != nullptr) m_spPlayerGameObject2->Destroy();

	m_spPlayerGameObject1 = nullptr;
	m_spPlayerGameObject2 = nullptr;

	++m_LevelNumber;

	m_Objects.clear();
}

void Level::LoadLevel()
{
	const LevelBlocks& selectedLevel{ m_Levels[m_LevelNumber] };

	glm::vec2 pos{}, offset{ minigin::Minigin::GetWindowWidth() / selectedLevel.Width, minigin::Minigin::GetWindowHeight() / selectedLevel.Height };

	for (size_t i = 0; i < selectedLevel.Width; i++)
	{
		for (size_t j = 0; j < selectedLevel.Height; j++)
		{
			if (selectedLevel.Blocks[i][j])
			{
				auto tile = make_shared<minigin::GameObject>();
				tile->SetTexture("Sprites/LevelTiles.png");
				tile->GetTransfrom()->SetPosition(pos.x, pos.y);
				tile->GetTransfrom()->SetScale(2.f, 2.f);

				tile->AddComponent(make_shared<minigin::BoxCollider>(tile->GetTextureSize().x, tile->GetTextureSize().y, false, false));
				tile->AddComponent(make_shared<minigin::RigidBodyComponent>(1.f, true));

				Add(tile);
			}
			pos.y += offset.y;
		}
		pos.x += offset.x;
		pos.y = 0.f;
	}
}

void Level::SetTwoPlayersSelected(bool value)
{
	m_TwoPlayersSelected = value;
}
