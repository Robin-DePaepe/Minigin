#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

void BaseComponent::SetGameObject(GameObject* owner)
{
	m_pGameObject = owner;
}

void BaseComponent::DeleteComponent()
{
	m_Delete = true;
}

std::shared_ptr<TransformComponent> BaseComponent::GetTransform() const
{
	if (m_pGameObject != nullptr) return m_pGameObject->GetTransfrom();

	return nullptr;
}


