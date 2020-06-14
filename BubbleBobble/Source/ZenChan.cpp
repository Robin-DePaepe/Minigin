#include "ZenChan.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "RigidBodyComponent.h"

ZenChan::ZenChan(const glm::vec2& pos,bool isMad, const wstring& name)
	:GameObject{name}
{
	if (isMad) 	SetTexture("Sprites/ZenChanMad.png");
	else 	SetTexture("Sprites/ZenChan.png");
	GetTransfrom()->SetPosition(pos.x, pos.y);

	if(isMad)	GetTransfrom()->SetScale(4.f, 4.f);
	else GetTransfrom()->SetScale(2.f, 2.f);

	AddComponent(make_shared<minigin::BoxCollider>(GetTextureSize().x, GetTextureSize().y, false, false));
	AddComponent(make_shared<minigin::RigidBodyComponent>(1.f, false));
}
