#pragma once

class GameObject;
class TransformComponent;

class BaseComponent
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent() = default;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Update() = 0;
	virtual void Render() const = 0;

	void SetGameObject(GameObject* owner);
	void DeleteComponent();

	GameObject* GetGameObject() const { return m_pGameObject; }
	bool Destoy() const { return m_Delete; }
	std::shared_ptr<TransformComponent> GetTransform() const;

protected:
	GameObject* m_pGameObject;
	bool m_Delete;
};

