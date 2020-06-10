#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

class TransformComponent final : public BaseComponent
{
public:
	//rule of 5
	TransformComponent() = default;
	~TransformComponent() = default;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	//getters
	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetRotation() const { return m_Rotation; }
	const glm::vec3& GetScale() const { return m_Scale; }

	//setters
	void SetPosition(float x, float y, float z = 0.f);
	void SetRotation(float x, float y, float z = 0.f);
	void SetScale(float x, float y, float z = 0.f);

	//transformations
	void Translate(float x, float y, float z = 0.f);
	void Rotate(float x, float y, float z = 0.f);
	void Scale(float x, float y, float z = 0.f);

	//other functions 
	void Update() override;
	void Render() const override;
private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};

