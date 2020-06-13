#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"

GameObject::GameObject(const std::string& name)
	:m_spTransform{ std::make_shared<TransformComponent>( )}
	, m_Name{name}
{}

GameObject::~GameObject() = default;

void GameObject::Update()
{
	m_spTransform->Update();

	for (std::shared_ptr<BaseComponent> spBaseComp : m_spComponents)
	{
		if (!spBaseComp->Enabled()) continue;
		spBaseComp->PhysxUpdate();
		spBaseComp->Update();
	}
	//delete components
	for (std::shared_ptr<BaseComponent> spBaseComp : m_spComponents)
	{
		if (spBaseComp->Destoy())
			m_spComponents.erase(std::find(m_spComponents.begin(), m_spComponents.end(), spBaseComp));
	}
}

void GameObject::Render() const
{
	const auto pos = m_spTransform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y);

	m_spTransform->Render();

	for (std::shared_ptr<BaseComponent> spBaseComp : m_spComponents)
	{
		if (!spBaseComp->Visible()) continue;

		spBaseComp->Render();
	}
}

void GameObject::SetTexture(const std::string& filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

glm::vec2 GameObject::GetTextureSize() const
{
	if (!m_spTexture) return glm::vec2{};

	return m_spTexture->GetSize();
}

std::shared_ptr<TransformComponent> GameObject::GetTransfrom() const
{
	return m_spTransform;
}

void GameObject::AddComponent(std::shared_ptr<BaseComponent> spComp)
{
	m_spComponents.push_back(spComp);
	spComp->SetGameObject(this);
	spComp->Initialize();
}

void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> spComp)
{
	auto it = std::find(m_spComponents.begin(), m_spComponents.end(), spComp);

	m_spComponents.erase(it);
	spComp->SetGameObject(nullptr);
}

void GameObject::onNotify(const BaseComponent& entity, Event event)
{
	switch (event)
	{
	case OnTiggerStay:
		//for the trigger events we pass the other object instead of the enitity itself
		OnTriggerStay(entity.GetGameObject());
		break;
	default:
		break;
	}
}


