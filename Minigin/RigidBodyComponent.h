#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <memory>
#include "Time.h"


namespace minigin
{
class ColliderComponent;

	class RigidBodyComponent final : public BaseComponent
	{
	public:
		//rule of 5
		RigidBodyComponent(float mass = 1.f, bool isStatic = false);
		~RigidBodyComponent() = default;

		RigidBodyComponent(const RigidBodyComponent& other) = delete;
		RigidBodyComponent(RigidBodyComponent&& other) = delete;
		RigidBodyComponent& operator=(const RigidBodyComponent& other) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent&& other) = delete;

		//functions
		void PhysxUpdate() override;
		void Update() override;
		void Render() const override {};
		void Initialize() override;

		void AddForce(glm::vec2 force);
		void ClearForce();

		bool IsStatic()  const { return m_IsStatic; }
		bool IsKinematic() const { return m_IsKinematic; }

		void SetKinematic(bool value) { m_IsKinematic = value; };

	private:
		const bool m_IsStatic;
		const float m_Gravity, m_Mass;
		const Time& m_Time;

		bool m_IsKinematic, m_Initialized;
		glm::vec2 m_Velocity;

		shared_ptr<TransformComponent> m_spTransform;
		shared_ptr<ColliderComponent> m_spCollider;
	};
}


