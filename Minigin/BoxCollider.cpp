#include "MiniginPCH.h"
#include "BoxCollider.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "TransformComponent.h"
#include "GameObject.h"
#include <SDL.h>
#include "Renderer.h"

minigin::BoxCollider::BoxCollider(float width, float height, bool isTrigger, bool visualizeBox)
	:ColliderComponent{ isTrigger }
	, m_Width{ width }
	, m_Height{ height }
	, m_VisualizeBox{ visualizeBox }
{}


void minigin::BoxCollider::PhysxUpdate()
{
	if (m_IsStatic && !m_IsTrigger) return;

	//setup vars
	m_BlockedLeft = false;
	m_BlockedRight = false;
	m_BlockedTop = false;
	m_OnGround = false;

	glm::vec2 bottomLeft{ GetTransform()->GetPosition() };
	bottomLeft.y += (m_Height * GetTransform()->GetScale().y);

	for (ColliderComponent* pCollider : m_pColliders)
	{
		BoxCollider* pBox = dynamic_cast<BoxCollider*>(pCollider);

		//no self check
		if (pBox == nullptr || pBox == this) continue;

		//non triggers will ignore  triggers
		if (!m_IsTrigger && pBox->IsTrigger()) continue;

		//vars
		const float widthBox2{ pBox->m_Width * pBox->GetTransform()->GetScale().x };
		const float heightBox2{ pBox->m_Height * pBox->GetTransform()->GetScale().y };

		glm::vec2 bottomLeftBox2{ pBox->GetTransform()->GetPosition() };
		bottomLeftBox2.y += (pBox->m_Height * pBox->GetTransform()->GetScale().y);

		//check for collision collision 
		if (bottomLeft.x < bottomLeftBox2.x + widthBox2 &&
			bottomLeft.x + (m_Width * GetTransform()->GetScale().x) > bottomLeftBox2.x&&
			bottomLeft.y < bottomLeftBox2.y + heightBox2 &&
			bottomLeft.y + (m_Height * GetTransform()->GetScale().y) > bottomLeftBox2.y)
		{
			//for the trigger events we pass the other object instead of the enitity itself
			if (m_IsTrigger) notify(*pCollider, Event::OnTiggerStay);
			else
			{
				//check if we are colliding into anything
				if (bottomLeft.y > pBox->GetTransform()->GetPosition().y&& GetTransform()->GetPosition().y < pBox->GetTransform()->GetPosition().y)
				{
					const float difference{ pBox->GetTransform()->GetPosition().y - bottomLeft.y };

					if (abs(difference) < 1.f)
					{
						m_OnGround = true;

						if (abs(difference) > 0.25f) GetTransform()->Translate(0.f, difference);
					}
				}

				if (GetTransform()->GetPosition().y < bottomLeftBox2.y && bottomLeft.y > bottomLeftBox2.y) m_BlockedTop = true;

				const float rightXValueBox1{ bottomLeft.x + m_Width * GetTransform()->GetScale().x };
				const float rightXValueBox2{ bottomLeftBox2.x + widthBox2 };
				const float wallBuffer{ 50.f };

				if (abs(pBox->GetTransform()->GetPosition().y - bottomLeft.y) < 0.25f) continue;

				if (bottomLeft.x - wallBuffer < rightXValueBox2 && rightXValueBox1 > rightXValueBox2) m_BlockedLeft = true;
				if (rightXValueBox1 + wallBuffer > bottomLeftBox2.x&& bottomLeft.x < bottomLeftBox2.x) m_BlockedRight = true;
			}
		}
	}
}

void minigin::BoxCollider::Update()
{
}

void minigin::BoxCollider::Render() const
{
	if (m_VisualizeBox)
	{
		glm::vec2 pos{ GetTransform()->GetPosition() };

		Renderer::GetInstance().RenderRect(SDL_Rect{ int(pos.x),int(pos.y), int(m_Width * GetTransform()->GetScale().x),int(m_Height * GetTransform()->GetScale().y) }, SDL_Color{ 0,255,0,150 });
	}
}

