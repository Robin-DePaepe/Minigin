#include "MiniginPCH.h"
#include "MovementControllerComponent.h"
#include "InputManager.h"
#include "TransformComponent.h"


using namespace std;

MovementControllerComponent::MovementControllerComponent(float speed, float jumpPower, int moveLeftButton, int moveRightButton, int jumpButton)
	:m_Speed{ speed }
	, m_JumpPower{ jumpPower }
	, m_spTransform{ GetTransform() }
	,m_Time{Time::GetInstance()}
{
	shared_ptr<Command> leftCommand = make_shared<MoveLeftCommand>(MoveLeftCommand{ this, &MovementControllerComponent::MoveLeft });
	InputManager::GetInstance().AddInput(InputAction(leftCommand, moveLeftButton, ControllerButton::DpadLeft, InputTriggerState::Down));

	shared_ptr<Command> rightCommand = make_shared<MoveRightCommand>(MoveRightCommand{ this, &MovementControllerComponent::MoveRight });
	InputManager::GetInstance().AddInput(InputAction(rightCommand, moveRightButton, ControllerButton::DpadRight, InputTriggerState::Down));

	shared_ptr<Command> jumpCommand = make_shared<JumpCommand>(JumpCommand{ this, &MovementControllerComponent::Jump });
	InputManager::GetInstance().AddInput(InputAction(jumpCommand, jumpButton, ControllerButton::ButtonA, InputTriggerState::Pressed));
}

void MovementControllerComponent::Update()
{
}

void MovementControllerComponent::MoveLeft()
{
	m_spTransform->Translate(-m_Speed * m_Time.GetElapsedTime(),0.f);
}

void MovementControllerComponent::MoveRight()
{
	m_spTransform->Translate(m_Speed * m_Time.GetElapsedTime(), 0.f);
}

void MovementControllerComponent::Jump()
{
	
}

void MoveLeftCommand::Execute()
{
	(m_Obj->*m_pFucntion)();
}

void MoveRightCommand::Execute()
{
	(m_Obj->*m_pFucntion)();
}

void JumpCommand::Execute()
{
	(m_Obj->*m_pFucntion)();
}
