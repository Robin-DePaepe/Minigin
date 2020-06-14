#include "Bubble.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "RigidBodyComponent.h"
#include "MovementControllerComponent.h"
#include "SceneManager.h"
#include "Melon.h"
#include "ZenChan.h"

Bubble::Bubble(const glm::vec2& spawnpos, bool goingLeft, const wstring& name)
	:GameObject{ name }
	, m_Dir{ 1 }
	, m_MaxCatchTime{ 1.5f }
	, m_MaxSurviveTime{ 5.f }
	, m_FloatingSpeed{ 30.f }
	, m_FireSpeed{ 250.f }
	, m_Timer{ 0.f }
	,m_ContainsEnemy{false}
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
	if (other->GetName() == L"Player" && (m_Timer > m_MaxCatchTime || m_ContainsEnemy))
	{
		//spawn pickup
		if (m_ContainsEnemy)
		{
			//setup a random position
			glm::vec2 pos{ GetTransfrom()->GetPosition() };
			int random{ rand() % 300 };

			if (pos.x - random < 5.f) pos.x += random;
			else pos.x -= random;

			random = rand() % 200;
			if (pos.y - random < 5.f) pos.y += random;
			else pos.y -= random;

			//create the object
			m_spObject = make_shared<Melon>(pos);
		}
		DestroyObject();
	}
	if (other->GetName() == L"Enemy" && m_Timer < m_MaxCatchTime)
	{
		m_ContainsEnemy = true;
		other->DestroyObject();
		m_Timer = 0.f;
		m_MaxSurviveTime *= 2.f;
	}
}

void Bubble::Update()
{
	m_Timer += minigin::Time::GetInstance().GetElapsedTime();

	if (m_Timer <= m_MaxCatchTime && !m_ContainsEnemy)
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
		//release angry enemy
		if (m_ContainsEnemy)	 m_spObject = make_shared<ZenChan>(GetTransfrom()->GetPosition(), true);

		DestroyObject();
	}
	GameObject::Update();
}

