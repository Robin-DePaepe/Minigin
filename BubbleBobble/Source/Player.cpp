#include "Player.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "RigidBodyComponent.h"
#include "MovementControllerComponent.h"
#include "SceneManager.h"
#include "Bubble.h"

Player::Player(const glm::vec2& pos, int moveLeftButton, minigin::ControllerButton moveLeftButtonC, int moveRightButton, minigin::ControllerButton moveRightButtonC, 
	int jumpButton, minigin::ControllerButton jumpButtonC, int fireButton, minigin::ControllerButton fireButtonC, const wstring& name)
	:GameObject{ name }
	, m_Lives{ 4 }
{
	//actions
	shared_ptr<minigin::Command> fireCommand = make_shared<FireCommand>(FireCommand{ this, &Player::FireBubble });
	m_FireId = minigin::InputManager::GetInstance().AddInput(minigin::InputAction(fireCommand, true, fireButton, fireButtonC, minigin::InputTriggerState::Pressed));

	//sprite
	SetTexture("Sprites/Player.png");
	GetTransfrom()->SetPosition(pos.x, pos.y);
	GetTransfrom()->SetScale(2.f, 2.f);

	//box collider non trigger
	AddComponent(make_shared<minigin::BoxCollider>(GetTextureSize().x, GetTextureSize().y, false, false));

	//box collider trigger
	AddComponent(make_shared<minigin::BoxCollider>(GetTextureSize().x, GetTextureSize().y, true, false));

	//add rigid body
	AddComponent(make_shared<minigin::RigidBodyComponent>());

	//add movement
	m_spMovement = make_shared<MovementControllerComponent>(25.f, 50.f, moveLeftButton, moveRightButton,jumpButton, moveLeftButtonC, moveRightButtonC, jumpButtonC);
	AddComponent(m_spMovement);
}

void Player::SetActions(bool active)
{
	GameObject::SetActions(active);

	minigin::InputManager::GetInstance().ChangeInputActionStatus(m_FireId, active);
}

void Player::OnTriggerStay(GameObject* other)
{
	if (other->GetName() == L"Enemy")
	{
		--m_Lives;

		if (m_Lives == 0) minigin::SceneManager::GetInstance().SetActiveGameScene(minigin::SceneManager::GetInstance().GetScene(L"Main Menu"));
	}
	if (other->GetName() == L"Pickup")
	{

	}
}

shared_ptr<minigin::GameObject> Player::GetBubble()
{
	auto copy = m_spBubble;

	m_spBubble = nullptr;

	return copy;
}

void FireCommand::Execute()
{
	(m_Obj->*m_pFucntion)();
}

void Player::FireBubble()
{
	m_spBubble = make_shared<Bubble>(GetTransfrom()->GetPosition(), m_spMovement->IsFacingLeft());
}
