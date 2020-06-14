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
{
	if (visualizeBox)
	{
		m_DebugBox = make_shared<GameObject>();
		m_DebugBox->SetTexture("DebugOverlay.png");
	}
}


void minigin::BoxCollider::PhysxUpdate()
{
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
				if (bottomLeft.y > pBox->GetTransform()->GetPosition().y&& GetTransform()->GetPosition().y < pBox->GetTransform()->GetPosition().y) m_OnGround = true;
				if (GetTransform()->GetPosition().y < bottomLeftBox2.y && bottomLeft.y > bottomLeftBox2.y) m_BlockedTop = true;

				float rightXValueBox1{ bottomLeft.x + m_Width * GetTransform()->GetScale().x };
				float rightXValueBox2{ bottomLeftBox2.x + widthBox2 };

				if (abs(pBox->GetTransform()->GetPosition().y - bottomLeft.y) < 0.25f) continue;

				if (bottomLeft.x < rightXValueBox2 && rightXValueBox1 > rightXValueBox2) m_BlockedLeft = true;
				if (rightXValueBox1 > bottomLeftBox2.x&& bottomLeft.x < bottomLeftBox2.x) m_BlockedRight = true;
			}
		}
	}
}

void minigin::BoxCollider::Update()
{
	if (m_VisualizeBox)
	{
		glm::vec2 pos = GetTransform()->GetPosition();
		m_DebugBox->GetTransfrom()->SetPosition(pos.x, pos.y);
	}
}

void minigin::BoxCollider::Render() const
{
	if (m_VisualizeBox)
	{
		glm::vec2 pos{ GetTransform()->GetPosition() };

		Renderer::GetInstance().RenderRect(SDL_Rect{ int(pos.x),int(pos.y), int(m_Width * GetTransform()->GetScale().x),int(m_Height * GetTransform()->GetScale().y) }, SDL_Color{ 0,255,0,150 });
	}
}

