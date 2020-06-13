#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

class TransformComponent final : public BaseComponent
{
public:
	//rule of 5
	TransformComponent();
	~TransformComponent() = default;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	//getters
	const glm::vec2& GetPosition() const { return m_Position; }
	const glm::vec2& GetRotation() const { return m_Rotation; }
	const glm::vec2& GetScale() const { return m_Scale; }

	//setters
	void SetPosition(float x, float y);
	void SetRotation(float x, float y);
	void SetScale(float x, float y);

	//transformations
	void Translate(float x, float y);
	void Rotate(float x, float y);
	void Scale(float x, float y);

	//other functions 
	void PhysxUpdate() override {};
	void Update() override {};
	void Render() const override {};
private:
	glm::vec2 m_Position;
	glm::vec2 m_Rotation;
	glm::vec2 m_Scale;
};

