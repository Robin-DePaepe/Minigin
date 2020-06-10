#pragma once
#include "BaseComponent.h"

class BoxColliderComponent final : public BaseComponent
{
public:
	//rule of 5
	BoxColliderComponent(float width, float height);
	~BoxColliderComponent() = default;

	BoxColliderComponent(const BoxColliderComponent& other) = delete;
	BoxColliderComponent(BoxColliderComponent&& other) = delete;
	BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
	BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;

	void Update() override;
	void Render() const override;

private:
	float m_Width, m_Height;
	
};

