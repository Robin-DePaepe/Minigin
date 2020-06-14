#include "Melon.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "RigidBodyComponent.h"


Melon::Melon(const glm::vec2& pos, const wstring& name)
	:GameObject{ name }
{
	SetTexture("Sprites/WaterMelon.png");
	GetTransfrom()->SetPosition(pos.x, pos.y);
	GetTransfrom()->SetScale(2.f, 2.f);

	AddComponent(make_shared<minigin::BoxCollider>(GetTextureSize().x, GetTextureSize().y, false, false));
	AddComponent(make_shared<minigin::RigidBodyComponent>(1.f,false));
}
