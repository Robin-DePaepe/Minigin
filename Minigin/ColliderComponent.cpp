#include "MiniginPCH.h"
#include "ColliderComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "TransformComponent.h"
#include "GameObject.h"
std::vector<ColliderComponent*> ColliderComponent::m_pColliders{};

ColliderComponent::ColliderComponent(bool isTrigger)
	:m_IsTrigger{ isTrigger }
	,m_OnGround{false}
	,m_BlockedRight{false}
	,m_BlockedLeft{false}
	,m_BlockedTop{false}
{
	m_pColliders.push_back(this);
}

ColliderComponent::~ColliderComponent()
{
	m_pColliders.erase(std::find(m_pColliders.cbegin(), m_pColliders.cend(), this));
}

void ColliderComponent::Initialize()
{
	addObserver(GetGameObject());
}

