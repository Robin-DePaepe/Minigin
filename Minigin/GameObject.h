#pragma once
#include "SceneObject.h"
#include "Observer.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace minigin
{
	class Texture2D;
	class TransformComponent;

	class GameObject : public SceneObject, public Observer<Event, BaseComponent>
	{
	public:
		//rule of 5
		GameObject(const wstring& name = L"");
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//functions
		virtual void Update() override;
		virtual void Render() const override;

		void SetTexture(const string& filename);
		glm::vec2 GetTextureSize() const;

		shared_ptr<TransformComponent> GetTransfrom() const;

		const wstring& GetName() const { return m_Name; }

		void AddComponent(shared_ptr<BaseComponent> pComp);
		void RemoveComponent(shared_ptr<BaseComponent> spComp);

		virtual void SetActions(bool active);

		virtual void onNotify(const BaseComponent& entity, Event event) override;

		virtual void OnTriggerStay(GameObject* other) { UNREFERENCED_PARAMETER(other); };

		//templated functions
#pragma region
		template <class T>
		shared_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			for (shared_ptr<BaseComponent> spBaseComp : m_spComponents)
			{
				if (spBaseComp && typeid(*spBaseComp) == ti)
					return static_pointer_cast<T>(spBaseComp);
			}
			return nullptr;
		}

		template <class T>
		vector<shared_ptr<T>> GetComponents()
		{
			const type_info& ti = typeid(T);
			vector<shared_ptr<T>> components;

			for (shared_ptr<BaseComponent> spBaseComp : m_spComponents)
			{
				if (spBaseComp && typeid(*spBaseComp) == ti)
					components.push_back(static_pointer_cast<T>(spBaseComp));
			}
			return components;
		}

#pragma endregion Template methods
	protected:
		//datamembers	
		shared_ptr<TransformComponent> m_spTransform;
		vector<shared_ptr<BaseComponent>> m_spComponents;
	private:
		shared_ptr<Texture2D> m_spTexture{};
		wstring m_Name;
	};
}
