#pragma once
#include "TransformComponent.h"
#include "SceneObject.h"
#include "BaseComponent.h"

class Texture2D;

using namespace std;

class GameObject final : public SceneObject
{
public:
	//functions
	void Update() override;
	void Render() const override;

	void SetTexture(const std::string& filename);
	std::shared_ptr<TransformComponent> GetTransfrom() const;

	void AddComponent(std::shared_ptr<BaseComponent> pComp);
	void RemoveComponent(std::shared_ptr<BaseComponent> spComp);

	//rule of 5
	GameObject(const std::string& name = "");
	virtual ~GameObject();

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

#pragma region
	template <class T>
	shared_ptr<T> GetComponent()
	{
		const type_info& ti = typeid(T);
		for (std::shared_ptr<BaseComponent> spBaseComp : m_spComponents)
		{
			if (spBaseComp && typeid(*spBaseComp) == ti)
				return static_pointer_cast<T>(spBaseComp);
		}
		return nullptr;
	}

	template <class T>
	std::vector<shared_ptr<T>> GetComponents()
	{
		const type_info& ti = typeid(T);
		std::vector<shared_ptr<T>> components;

		for (std::shared_ptr<BaseComponent> spBaseComp : m_spComponents)
		{
			if (spBaseComp && typeid(*spBaseComp) == ti)
				components.push_back(static_pointer_cast<T>(spBaseComp));
		}
		return components;
	}

#pragma endregion Template methods
private:
	//datamembers	
	std::shared_ptr<TransformComponent> m_spTransform;
	std::vector<std::shared_ptr<BaseComponent>> m_spComponents;
	std::shared_ptr<Texture2D> m_spTexture{};
	std::string m_Name;
};

