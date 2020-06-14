#include "MiniginPCH.h"
#include "MovementControllerComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Minigin.h"

using namespace std;


MovementControllerComponent::MovementControllerComponent(float speed, float jumpPower, int moveLeftButton, int moveRightButton, int jumpButton, 
	minigin::ControllerButton moveLeftButtonC, minigin::ControllerButton moveRightButtonC, minigin::ControllerButton jumpButtonC)
	:m_Speed{ speed }
	, m_JumpPower{ jumpPower }
	, m_Time{ minigin::Time::GetInstance() }
	, m_Initialized{ false }
	, m_InputManager{ minigin::InputManager::GetInstance() }
	, m_FacingLeft{ false }
{
	//actions
	shared_ptr<minigin::Command> leftCommand = make_shared<MoveLeftCommand>(MoveLeftCommand{ this, &MovementControllerComponent::MoveLeft });
	m_ActionIds.push_back(m_InputManager.AddInput(minigin::InputAction(leftCommand, true, moveLeftButton, moveLeftButtonC, minigin::InputTriggerState::Down)));

	shared_ptr<minigin::Command> rightCommand = make_shared<MoveRightCommand>(MoveRightCommand{ this, &MovementControllerComponent::MoveRight });
	m_ActionIds.push_back(m_InputManager.AddInput(minigin::InputAction(rightCommand, true, moveRightButton, moveRightButtonC, minigin::InputTriggerState::Down)));

	shared_ptr<minigin::Command> jumpCommand = make_shared<JumpCommand>(JumpCommand{ this, &MovementControllerComponent::Jump });
	m_ActionIds.push_back(m_InputManager.AddInput(minigin::InputAction(jumpCommand, true, jumpButton, jumpButtonC, minigin::InputTriggerState::Pressed)));

	//sound
	minigin::SoundManager::GetInstance().GetSystem()->createSound("Resources/Sounds/Jump.wav", FMOD_2D, nullptr, &m_pSound);
	minigin::SoundManager::GetInstance().GetSystem()->playSound(m_pSound, 0, false, &m_pChannel);
}

void MovementControllerComponent::Initialize()
{
	if (m_pGameObject != nullptr) m_spRigid = m_pGameObject->GetComponent<minigin::RigidBodyComponent>();
	if (m_spRigid == nullptr) minigin::Logger::LogError(L"The movement controller needs a rigidbody to function properly");

	if (m_pGameObject != nullptr)
	{
		auto colliders = m_pGameObject->GetComponents<minigin::BoxCollider>();

		for (size_t i = 0; i < colliders.size(); i++)
		{
			if (colliders[i]->IsTrigger() == false) m_spCollider = colliders[i];
		}
		if (m_spCollider == nullptr) minigin::Logger::LogError(L"The Movement controller needs a non trigger collider to function properly");
	}

	m_spTransform = GetTransform();

	m_Initialized = true;
}

void MovementControllerComponent::Update()
{
	if (m_Initialized == false) minigin::Logger::LogError(L"Movement component hasn't been initialized");

	//if the player falls through the bottom he respawns at the top
	if (GetTransform()->GetPosition().y > minigin::Minigin::GetWindowHeight()) GetTransform()->SetPosition(GetTransform()->GetPosition().x, 0.f);
	if (GetTransform()->GetPosition().y <= -1.f) m_spRigid->ClearForce();
}

void MovementControllerComponent::SetActions(bool active)
{
	for (size_t id : m_ActionIds) m_InputManager.ChangeInputActionStatus(id, active);
}

void MovementControllerComponent::MoveLeft()
{
	if (m_spCollider->IsBlockedLeft()) return;

	m_spTransform->Translate(-m_Speed * m_Time.GetElapsedTime(), 0.f);
	m_FacingLeft = true;
}

void MovementControllerComponent::MoveRight()
{
	if (m_spCollider->IsBlockedRight()) return;

	m_spTransform->Translate(m_Speed * m_Time.GetElapsedTime(), 0.f);
	m_FacingLeft = false;
}

void MovementControllerComponent::Jump()
{
	if (!m_spCollider->IsOnGround()) return;

	minigin::SoundManager::GetInstance().GetSystem()->playSound(m_pSound, 0, false, &m_pChannel);

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
