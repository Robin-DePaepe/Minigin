#include "MiniginPCH.h"
#include "TestScene1.h"
#include "InputManager.h"

TestScene1::TestScene1(const std::wstring& name)
	:Scene{name}
{
    
}

TestScene1::~TestScene1()
{
    m_pSound->release();
}

void TestScene1::Initialize()
{
	SoundManager::GetInstance().GetSystem()->createSound("Resources/Sounds/arena_champ.wav", FMOD_2D, nullptr, &m_pSound);
    shared_ptr<Command> test = make_shared<TestCommand>(TestCommand{});
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
}

void TestCommand::Execute()
{
    std::cout <<  "Called\n";
}
