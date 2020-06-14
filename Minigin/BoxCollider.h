#pragma once
#include "ColliderComponent.h"
#include <vector>

namespace minigin
{
	class BoxCollider final : public ColliderComponent
	{
	public:
		//rule of 5
		BoxCollider(float width, float height, bool isTrigger, bool visualizeBox);
		~BoxCollider() = default;

		BoxCollider(const BoxCollider& other) = delete;
		BoxCollider(BoxCollider&& other) = delete;
		BoxCollider& operator=(const BoxCollider& other) = delete;
		BoxCollider& operator=(BoxCollider&& other) = delete;

		//functions
		void PhysxUpdate() override;
		void Update() override;
		void Render() const override;

	private:
		//datamembers
		bool m_VisualizeBox;
		float m_Width, m_Height;
		shared_ptr<GameObject> m_DebugBox;
	};
}
