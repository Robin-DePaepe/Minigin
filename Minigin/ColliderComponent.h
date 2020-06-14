#pragma once
#include "BaseComponent.h"
#include <vector>


namespace minigin
{
	class ColliderComponent : public BaseComponent
	{
	public:
		//rule of 5
		ColliderComponent(bool isTrigger);
		~ColliderComponent();

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		//functions
		void Initialize() override;
		virtual void PhysxUpdate() override {};
		virtual void Update() override {};
		virtual void Render() const override {};

		bool IsTrigger() const { return m_IsTrigger; }
		bool SetTrigger(bool value) { m_IsTrigger = value; }

		bool IsOnGround() const { return m_OnGround; }
		bool IsBlockedLeft() const { return m_BlockedLeft; }
		bool IsBlockedRight() const { return m_BlockedRight; }
		bool IsBlockedTop() const { return m_BlockedTop; }

	protected:
		//datamembers
		bool m_OnGround, m_BlockedLeft, m_BlockedRight, m_BlockedTop, m_IsTrigger;
		static vector<ColliderComponent*> m_pColliders;
	};
}
