#pragma once
#include "Subject.h"

namespace minigin
{
	class GameObject;
	class TransformComponent;

	enum class Event
	{
		OnTiggerStay
	};

	class BaseComponent : public Subject<Event, BaseComponent>
	{
	public:
		//rule of 5
		BaseComponent();
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		//functions
		virtual void Initialize() {};
		virtual void Update() = 0;
		virtual void PhysxUpdate() = 0;
		virtual void Render() const = 0;

		virtual void SetActions(bool active) { UNREFERENCED_PARAMETER(active); };

		void SetGameObject(GameObject* owner);
		void DeleteComponent();

		bool Enabled() const { return m_Enabled; }
		bool SetEnabled(bool value) { m_Enabled = value; }

		bool Visible() const { return m_Visible; }
		bool SetVisible(bool value) { m_Visible = value; }

		bool Destoy() const { return m_Delete; }
		void DestoyComponent(bool value) { m_Delete = value; }

		GameObject* GetGameObject() const { return m_pGameObject; }
		shared_ptr<TransformComponent> GetTransform() const;

	protected:
		//datamembers
		GameObject* m_pGameObject;
		bool m_Delete, m_Visible, m_Enabled;
	};
}