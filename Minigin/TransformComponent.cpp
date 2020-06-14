#include "MiniginPCH.h"
#include "TransformComponent.h"


minigin::TransformComponent::TransformComponent()
	:m_Scale{1.f,1.f}
{
}

void  minigin::TransformComponent::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void  minigin::TransformComponent::SetRotation(float x, float y)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
}

void  minigin::TransformComponent::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void  minigin::TransformComponent::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
}

void  minigin::TransformComponent::Rotate(float x, float y)
{
	m_Rotation.x += x;
	m_Rotation.y += y;
}

void  minigin::TransformComponent::Scale(float x, float y)
{
	m_Scale.x += x;
	m_Scale.y += y;
}
