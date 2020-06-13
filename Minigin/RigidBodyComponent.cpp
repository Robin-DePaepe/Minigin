#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

RigidBodyComponent::RigidBodyComponent(bool isStatic)
	:m_IsKinematic{false}
	,m_IsStatic{ isStatic }
	, m_spTransform{ GetTransform() }
	, m_Time{ Time::GetInstance() }
	,m_Gravity{9.81f}
{
}

void RigidBodyComponent::Update()
{
	if (m_IsStatic) return;

	if (true && !m_IsKinematic)//check for in the air
	{
	m_Velocity.y -= m_Time.GetElapsedTime() * m_Gravity;
	}

	glm::vec3 translation{ m_Velocity * m_Time.GetElapsedTime() };
	m_spTransform->Translate(translation.x,translation.y,translation.z);
}

void RigidBodyComponent::AddForce(glm::vec3 force)
{
	m_Velocity += force;
}

void RigidBodyComponent::ClearForce()
{
	m_Velocity = glm::vec3{ 0.f,0.f,0.f };
}
