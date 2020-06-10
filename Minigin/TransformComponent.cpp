#include "MiniginPCH.h"
#include "TransformComponent.h"


void TransformComponent::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void TransformComponent::SetRotation(float x, float y)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
}

void TransformComponent::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void TransformComponent::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
}

void TransformComponent::Rotate(float x, float y)
{
	m_Rotation.x += x;
	m_Rotation.y += y;
}

void TransformComponent::Scale(float x, float y)
{
	m_Scale.x += x;
	m_Scale.y += y;
}

void TransformComponent::Update()
{

}

void TransformComponent::Render() const
{}
