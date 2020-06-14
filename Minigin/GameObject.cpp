#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include <SDL.h>

minigin::GameObject::GameObject(const wstring& name)
	:m_spTransform{ make_shared<TransformComponent>() }
	, m_Name{ name }
{}

minigin::GameObject::~GameObject() = default;

void minigin::GameObject::Update()
{
	m_spTransform->Update();

	for (shared_ptr<BaseComponent> spBaseComp : m_spComponents)
	{
		if (!spBaseComp->Enabled()) continue;

		spBaseComp->PhysxUpdate();
		spBaseComp->Update();
	}
	//delete components
	auto it = m_spComponents.begin();

	while (it != m_spComponents.cend())
	{
		if ((*it)->Destroy()) it = m_spComponents.erase(it);
		else ++it;
	}
}

void minigin::GameObject::Render() const
{
	if (!m_Visible) return;

	SDL_Rect dst;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	const auto pos = m_spTransform->GetPosition();

	Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y, dst.w * m_spTransform->GetScale().x, dst.h * m_spTransform->GetScale().y);

	m_spTransform->Render();

	for (shared_ptr<BaseComponent> spBaseComp : m_spComponents)
	{
		if (!spBaseComp->Visible()) continue;

		spBaseComp->Render();
	}
}


void minigin::GameObject::SetTexture(const string & filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

glm::vec2 minigin::GameObject::GetTextureSize() const
{
	if (!m_spTexture) return glm::vec2{};

	return m_spTexture->GetSize();
}

shared_ptr<minigin::GameObject> minigin::GameObject::GetNewObject()
{
	auto copy = m_spObject;

	m_spObject = nullptr;

	return copy;
}

shared_ptr<minigin::TransformComponent> minigin::GameObject::GetTransfrom() const
{
	return m_spTransform;
}

void minigin::GameObject::AddComponent(shared_ptr<BaseComponent> spComp)
{
	m_spComponents.push_back(spComp);
	spComp->SetGameObject(this);
	spComp->Initialize();
}

void minigin::GameObject::RemoveComponent(shared_ptr<BaseComponent> spComp)
{
	auto it = find(m_spComponents.begin(), m_spComponents.end(), spComp);

	m_spComponents.erase(it);
	spComp->SetGameObject(nullptr);
}

void minigin::GameObject::SetActions(bool active)
{
	for (shared_ptr<BaseComponent> spBaseComp : m_spComponents)		spBaseComp->SetActions(active);
}

void minigin::GameObject::onNotify(const BaseComponent & entity, Event event)
{
	switch (event)
	{
	case  Event::OnTiggerStay:
		//for the trigger events we pass the other object instead of the enitity itself
		OnTriggerStay(entity.GetGameObject());
		break;
	default:
		break;
	}
}


