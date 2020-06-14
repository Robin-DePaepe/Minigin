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

shared_ptr<TransformComponent> BaseComponent::GetTransform() const
{
	if (m_pGameObject != nullptr) return m_pGameObject->GetTransfrom();

	Logger::LogWarning(L"Returning empty transform.\n");
	return nullptr;
}

BaseComponent::BaseComponent()
	:m_pGameObject{nullptr}
	,m_Delete{false}
	,m_Enabled{true}
	,m_Visible{true}
{
}
