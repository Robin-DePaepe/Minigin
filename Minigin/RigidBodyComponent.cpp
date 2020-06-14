#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include <algorithm>

minigin::RigidBodyComponent::RigidBodyComponent(float mass, bool isStatic)
	:m_IsKinematic{ false }
	, m_IsStatic{ isStatic }
	, m_Time{ Time::GetInstance() }
	, m_Gravity{ 9.81f }
	, m_Initialized{ false }
	, m_Mass{ mass }
	,m_MaxAxisSpeed{200.f}
{
}

void  minigin::RigidBodyComponent::PhysxUpdate()
{
}

void  minigin::RigidBodyComponent::Update()
{
	if (!m_Initialized) Logger::LogError(L"Rigidbody component hasn't been initialized");

	if (m_IsStatic) return;

	//check if we want to apply gravity
	if (!m_spCollider->IsOnGround() && !m_IsKinematic) m_Velocity.y += m_Time.GetElapsedTime() * m_Gravity * m_Mass;
	//reset the y velocity when landing
	if (m_spCollider->IsOnGround() && m_Velocity.y > 0.f) m_Velocity.y = 0.f;

	//clamp axis speed
	if (m_Velocity.y >= m_MaxAxisSpeed) m_Velocity.y = m_MaxAxisSpeed;
	//move the object
	glm::vec2 translation{ m_Velocity * m_Time.GetElapsedTime() };

	m_spTransform->Translate(translation.x, translation.y);
}

void  minigin::RigidBodyComponent::Initialize()
{
	if (m_pGameObject != nullptr)
	{
		auto colliders = m_pGameObject->GetComponents<minigin::BoxCollider>();

		for (size_t i = 0; i < colliders.size(); i++)
		{
			if (colliders[i]->IsTrigger() == false) m_spCollider = colliders[i];
		}
		if (m_spCollider == nullptr) minigin::Logger::LogError(L"The Rigid body needs a non trigger collider to function properly");
		else m_spCollider->SetIsStatic(m_IsStatic);
	}
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
