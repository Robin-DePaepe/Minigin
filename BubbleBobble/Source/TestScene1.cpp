#include "MiniginPCH.h"
#include "TestScene1.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextObject.h"
#include "WalkingState.h"
#include "JumpingState.h"

TestScene1::TestScene1(const std::wstring& name)
	:Scene{name}
    , m_pTestStateManager{ new TestStatesManager()}
{
     auto go = std::make_shared<GameObject>();
    go->SetTexture("background.jpg");
    Add(go);

    go = std::make_shared<GameObject>();
    go->SetTexture("logo.png");
    go->GetTransfrom()->SetPosition(216.f, 180.f);
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
    shared_ptr<Command> test = make_shared<TestCommand>( TestCommand{m_pTestStateManager, &TestStatesManager::SlapAss});
    InputManager::GetInstance().AddInput(InputAction(test, VK_LBUTTON, ControllerButton::ButtonY, InputTriggerState::Released));

    SoundManager::GetInstance().GetSystem()->playSound(m_pSound, 0, false, &m_pChannel);

}

void TestScene1::Update()
{
 if(InputManager::GetInstance().IsDown('W'))			std::cout << "Down \n";
 if(InputManager::GetInstance().IsReleased('A'))			std::cout << "\n released \n";
 if(InputManager::GetInstance().IsPressed('Q'))			std::cout << "\npressed \n";

 if(InputManager::GetInstance().IsDown(ControllerButton::ButtonA))			std::cout << "Down \n";
 if(InputManager::GetInstance().IsReleased(ControllerButton::ButtonA))			std::cout << "\n released \n";
 if(InputManager::GetInstance().IsPressed(ControllerButton::ButtonA))			std::cout << "\npressed \n";

 int x{}, y{};
 InputManager::GetInstance().GetMousePos(x,y);

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
