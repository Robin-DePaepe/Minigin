#include "MiniginPCH.h"
#include "MovementControllerComponent.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "BoxCollider.h"

using namespace std;

MovementControllerComponent::MovementControllerComponent(float speed, float jumpPower, int moveLeftButton, int moveRightButton, int jumpButton)
	:m_Speed{ speed }
	, m_JumpPower{ jumpPower }
	, m_Time{ Time::GetInstance() }
	, m_Initialized{false}
{
	shared_ptr<Command> leftCommand = make_shared<MoveLeftCommand>(MoveLeftCommand{ this, &MovementControllerComponent::MoveLeft });
	InputManager::GetInstance().AddInput(InputAction(leftCommand, moveLeftButton, ControllerButton::DpadLeft, InputTriggerState::Down));

	shared_ptr<Command> rightCommand = make_shared<MoveRightCommand>(MoveRightCommand{ this, &MovementControllerComponent::MoveRight });
	InputManager::GetInstance().AddInput(InputAction(rightCommand, moveRightButton, ControllerButton::DpadRight, InputTriggerState::Down));

	shared_ptr<Command> jumpCommand = make_shared<JumpCommand>(JumpCommand{ this, &MovementControllerComponent::Jump });
	InputManager::GetInstance().AddInput(InputAction(jumpCommand, jumpButton, ControllerButton::ButtonA, InputTriggerState::Pressed));
}

void MovementControllerComponent::Initialize()
{
	if (m_pGameObject != nullptr) m_spRigid = m_pGameObject->GetComponent<RigidBodyComponent>();
	if (m_spRigid == nullptr) Logger::LogError(L"The movement controller needs a rigidbody to function properly");

	if (m_pGameObject != nullptr) m_spCollider = m_pGameObject->GetComponent<BoxCollider>();
	if (m_spCollider == nullptr) Logger::LogError(L"The Movement controller needs a collider to function properly");

	m_spTransform = GetTransform();

	m_Initialized = true;
}

void MovementControllerComponent::Update()
{
	if (m_Initialized == false) Logger::LogError(L"Movement component hasn't been initialized");
}

void MovementControllerComponent::MoveLeft()
{
	if (m_spCollider->IsBlockedLeft()) return;

	m_spTransform->Translate(-m_Speed * m_Time.GetElapsedTime(), 0.f);
}

void MovementControllerComponent::MoveRight()
{
	if (m_spCollider->IsBlockedRight()) return;

	m_spTransform->Translate(m_Speed * m_Time.GetElapsedTime(), 0.f);
}

void MovementControllerComponent::Jump()
{
	if (!m_spCollider->IsOnGround()) return;

	m_spRigid->AddForce({ 0.f,m_JumpPower });
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
