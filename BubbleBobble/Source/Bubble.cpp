#include "Bubble.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "RigidBodyComponent.h"
#include "MovementControllerComponent.h"
#include "SceneManager.h"

Bubble::Bubble(const glm::vec2& spawnpos, bool goingLeft, const wstring& name)
	:GameObject{ name }
	, m_Dir{ 1 }
	, m_MaxCatchTime{ 1.5f }
	, m_MaxSurviveTime{ 5.f }
	, m_FloatingSpeed{ 30.f }
	, m_FireSpeed{ 250.f }
	, m_Timer{ 0.f }
{
	//sprite
	SetTexture("Sprites/Bubble.png");
	GetTransfrom()->SetPosition(spawnpos.x, spawnpos.y);
	GetTransfrom()->SetScale(2.f, 2.f);

	//box collider trigger
	AddComponent(make_shared<minigin::BoxCollider>(GetTextureSize().x, GetTextureSize().y, true, false));

	if (goingLeft) m_Dir *= -1.f;
}


void Bubble::OnTriggerStay(GameObject* other)
{
	if (other->GetName() == L"Player" && m_Timer > m_MaxCatchTime)
	{
		DestroyObject();
	}
}

void Bubble::Update()
{
	m_Timer += minigin::Time::GetInstance().GetElapsedTime();

	if (m_Timer <= m_MaxCatchTime)
	{
		GetTransfrom()->Translate(minigin::Time::GetInstance().GetElapsedTime() * m_Dir * m_FireSpeed, 0.f);
	}
	else if (m_Timer <= m_MaxSurviveTime)
	{
		float y{ 0.f };

		//stops the bubble at the top
		if (GetTransfrom()->GetPosition().y > 25.f) y = minigin::Time::GetInstance().GetElapsedTime() * -m_FloatingSpeed;

		GetTransfrom()->Translate(minigin::Time::GetInstance().GetElapsedTime() * m_FireSpeed * m_Dir, y);
		m_Dir *= -1.f;
	}
	else
	{
		DestroyObject();
	}
	GameObject::Update();

}
