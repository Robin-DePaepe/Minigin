#pragma once
#include "Subject.h"

class GameObject;
class TransformComponent;

enum Event
{
	OnTiggerStay
};

class BaseComponent : public Subject<Event,BaseComponent>
{
public:
	BaseComponent();
	virtual ~BaseComponent() = default;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Initialize()  {};
	virtual void Update() = 0;
	virtual void PhysxUpdate() = 0;
	virtual void Render() const = 0;

	void SetGameObject(GameObject* owner);
	void DeleteComponent();
	
	bool Enabled() const { return m_Enabled; }
	bool SetEnabled(bool value) { m_Enabled = value; }	

	bool Visible() const { return m_Visible; }
	bool SetVisible(bool value) { m_Visible = value; }

	bool Destoy() const { return m_Delete; }
	void DestoyComponent(bool value)  {  m_Delete = value; }

	GameObject* GetGameObject() const { return m_pGameObject; }
	shared_ptr<TransformComponent> GetTransform() const;

protected:
	GameObject* m_pGameObject;
	bool m_Delete,m_Visible,m_Enabled;
};

