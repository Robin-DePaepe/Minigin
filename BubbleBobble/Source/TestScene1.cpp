#include "MiniginPCH.h"
#include "TestScene1.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextObject.h"
#include "WalkingState.h"
#include "JumpingState.h"
#include "MovementControllerComponent.h"
#include "RigidBodyComponent.h"
#include "BoxCollider.h"

TestScene1::TestScene1(const std::wstring& name)
	:Scene{ name }
	, m_pTestStateManager{ new TestStatesManager() }
{
	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	Add(go);

	//logo1
	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->GetTransfrom()->SetPosition(316.f, 210.f);
	go->GetTransfrom()->SetScale(5.f, 1.f);

	go->AddComponent(make_shared<BoxCollider>(100.f, 25.f, false,true));

	auto rigid{ make_shared<RigidBodyComponent>() };
	rigid->SetKinematic(true);
	go->AddComponent(rigid);

	auto movement{ make_shared<MovementControllerComponent>(25.f,50.f,'A','D', 'S') };
	go->AddComponent(movement);


	Add(go);

	//logo2
	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->GetTransfrom()->SetPosition(260.f, 150.f);

	go->AddComponent(make_shared<BoxCollider>(100.f, 25.f, false,true));

	rigid = { make_shared<RigidBodyComponent>(3.f)};
	go->AddComponent(rigid);

	movement = { make_shared<MovementControllerComponent>(25.f,50.f,'J','K', 'W') };
	go->AddComponent(movement);

	Add(go);


	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 32);

	Add(to);

	m_pTestStateManager->AddState(TestStates::walking, new WalkingState{});
	m_pTestStateManager->AddState(TestStates::jumping, new JumpingState{}, true);
}

TestScene1::~TestScene1()
{
	m_pSound->release();
}
void testf()
{
	Logger::LogInfo(L"ha");
}
void TestScene1::Initialize()
{
	SoundManager::GetInstance().GetSystem()->createSound("Resources/Sounds/arena_champ.wav", FMOD_2D, nullptr, &m_pSound);
	shared_ptr<Command> test = make_shared<TestCommand>(TestCommand{ m_pTestStateManager, &TestStatesManager::SlapAss });
	InputManager::GetInstance().AddInput(InputAction(test, VK_LBUTTON, ControllerButton::ButtonY, InputTriggerState::Released));

	//SoundManager::GetInstance().GetSystem()->playSound(m_pSound, 0, false, &m_pChannel);

}

void TestScene1::Update()
{
	int x{}, y{};
	InputManager::GetInstance().GetMousePos(x, y);
	//std::cout << x << "     " << y << std::endl;
	m_pTestStateManager->Update();
}

void TestScene1::Render() const
{
}



void TestScene1::SceneActivated()
{
	m_pChannel->setPaused(false);

}

void TestScene1::SceneDeactivated()
{
	m_pChannel->setPaused(true);
	static_cast<TestStatesManager*>(m_pTestStateManager)->SlapAss();
}

void TestCommand::Execute()
{
	(m_Obj->*m_pFucntion)();
}
