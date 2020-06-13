#pragma once
#include "BaseComponent.h"
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include <memory>
#include "Time.h"

class RigidBodyComponent final : public BaseComponent
{
public:
	//rule of 5
	RigidBodyComponent(bool isStatic = false);
	~RigidBodyComponent() = default;

	RigidBodyComponent(const RigidBodyComponent& other) = delete;
	RigidBodyComponent(RigidBodyComponent&& other) = delete;
	RigidBodyComponent& operator=(const RigidBodyComponent& other) = delete;
	RigidBodyComponent& operator=(RigidBodyComponent&& other) = delete;

	void Update() override;
	void Render() const override {};

	void AddForce(glm::vec3 force);
	void ClearForce();

	bool IsStatic()  const { return m_IsStatic; }
	bool IsKinematic() const { return m_IsKinematic; }

	void SetKinematic(bool value) { m_IsKinematic = value; };

private:
	const bool m_IsStatic;
	bool m_IsKinematic;
	glm::vec3 m_Velocity;
	const float m_Gravity;
	const std::shared_ptr<TransformComponent> m_spTransform;
	const Time& m_Time;
};



