#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "BoxCollider.h"

minigin::RigidBodyComponent::RigidBodyComponent(float mass,bool isStatic)
	:m_IsKinematic{ false }
	, m_IsStatic{ isStatic }
	, m_Time{ Time::GetInstance() }
	, m_Gravity{ 9.81f }
	, m_Initialized{ false }
	, m_Mass{mass}
{
}

void  minigin::RigidBodyComponent::PhysxUpdate()
{
}

void  minigin::RigidBodyComponent::Update()
{
	if (!m_Initialized) Logger::LogError(L"Rigidbody component hasn't been initialized");

	if (m_IsStatic) return;

	if (!m_spCollider->IsOnGround() && !m_IsKinematic)//check for in the air
	{
		m_Velocity.y += m_Time.GetElapsedTime() * m_Gravity * m_Mass;
	}

	if (m_spCollider->IsOnGround() && m_Velocity.y > 0.f) m_Velocity.y = 0.f;

	glm::vec2 translation{ m_Velocity * m_Time.GetElapsedTime() };

	m_spTransform->Translate(translation.x, translation.y);
}

void  minigin::RigidBodyComponent::Initialize()
{
	if (m_pGameObject != nullptr) m_spCollider = m_pGameObject->GetComponent<BoxCollider>();
	if (m_spCollider == nullptr) Logger::LogError(L"The Rigid body  needs a collider to function properly");

	m_spTransform = GetTransform();

	m_Initialized = true;
}

void  minigin::RigidBodyComponent::AddForce(glm::vec2 force)
{
	m_Velocity -= force;
}

void  minigin::RigidBodyComponent::ClearForce()
{
	m_Velocity = glm::vec2{ 0.f,0.f };
}
