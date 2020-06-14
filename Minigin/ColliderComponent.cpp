#include "MiniginPCH.h"
#include "ColliderComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "TransformComponent.h"
#include "GameObject.h"


vector<minigin::ColliderComponent*>  minigin::ColliderComponent::m_pColliders{};

minigin::ColliderComponent::ColliderComponent(bool isTrigger)
	:m_IsTrigger{ isTrigger }
	, m_OnGround{ false }
	, m_BlockedRight{ false }
	, m_BlockedLeft{ false }
	, m_BlockedTop{ false }
{
	m_pColliders.push_back(this);
}

minigin::ColliderComponent::~ColliderComponent()
{
	m_pColliders.erase(find(m_pColliders.cbegin(), m_pColliders.cend(), this));
}

void  minigin::ColliderComponent::Initialize()
{
	addObserver(GetGameObject());
}

