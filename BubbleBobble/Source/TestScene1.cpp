#include "MiniginPCH.h"
#include "TestScene1.h"
#include "InputManager.h"

TestScene1::TestScene1(const std::wstring& name)
	:Scene{name}
{
    
}

void TestScene1::Initialize()
{
	SoundManager::GetInstance().GetSystem()->createSound("Resources/Sounds/arena_champ.wav", FMOD_2D, nullptr, &m_pSound);
    shared_ptr<Command> test = make_shared<TestCommand>(TestCommand{});
    InputManager::GetInstance().AddInput(InputAction(test, 'S', ControllerButton::none, InputTriggerState::Pressed));
    InputManager::GetInstance().AddInput(InputAction(test, -1, ControllerButton::ButtonY, InputTriggerState::Released));
}

void TestScene1::Update()
{
 if(InputManager::GetInstance().IsDown('W'))			std::cout << "Down \n";
 if(InputManager::GetInstance().IsReleased('W'))			std::cout << "\n released \n";
 if(InputManager::GetInstance().IsPressed('W'))			std::cout << "\npressed \n";

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
	SoundManager::GetInstance().GetSystem()->playSound(m_pSound, 0, false, &m_pChannel);
}

void TestScene1::SceneDeactivated()
{
	m_pSound->release();
}

void TestCommand::Execute()
{
    std::cout <<  "Called\n";
}
