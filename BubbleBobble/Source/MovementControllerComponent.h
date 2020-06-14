#pragma once
#include "RigidBodyComponent.h"
#include "BoxCollider.h"
#include "InputManager.h"
#include "BaseComponent.h"
#include "Command.h"
#include "Time.h"
#include <memory>
#include <vector>
#include <fmod.hpp>

class MovementControllerComponent;

#pragma region MovementCommands
class MoveLeftCommand final : public minigin::Command
{
public:
	MoveLeftCommand(MovementControllerComponent* pObj, void(MovementControllerComponent::* pFucntion)())
		:Command{}
		, m_Obj{ pObj }
		, m_pFucntion{ pFucntion }
	{};

	virtual void Execute()  override;
	virtual void Undo() override {};
private:
	MovementControllerComponent* m_Obj;
	void(MovementControllerComponent::* m_pFucntion)();
};

class MoveRightCommand final : public minigin::Command
{
public:
	MoveRightCommand(MovementControllerComponent* pObj, void(MovementControllerComponent::* pFucntion)())
		:Command{}
		, m_Obj{ pObj }
		, m_pFucntion{ pFucntion }
	{};

	virtual void Execute()  override;
	virtual void Undo() override {};
private:
	MovementControllerComponent* m_Obj;
	void(MovementControllerComponent::* m_pFucntion)();
};

class JumpCommand final : public minigin::Command
{
public:
	JumpCommand(MovementControllerComponent* pObj, void(MovementControllerComponent::* pFucntion)())
		:Command{}
		, m_Obj{ pObj }
		, m_pFucntion{ pFucntion }
	{};

	virtual void Execute()  override;
	virtual void Undo() override {};
private:
	MovementControllerComponent* m_Obj;
	void(MovementControllerComponent::* m_pFucntion)();
};
#pragma endregion MovementCommands


class MovementControllerComponent final : public minigin::BaseComponent
{
public:
	//rule of 5
	MovementControllerComponent(float speed, float jumpPower, int moveLeftButton,int moveRightButton, int jumpButton, minigin::ControllerButton moveLeftButtonC
		, minigin::ControllerButton moveRightButtonC, minigin::ControllerButton jumpButtonC);
	~MovementControllerComponent() = default;

	MovementControllerComponent(const MovementControllerComponent& other) = delete;
	MovementControllerComponent(MovementControllerComponent&& other) = delete;
	MovementControllerComponent& operator=(const MovementControllerComponent& other) = delete;
	MovementControllerComponent& operator=(MovementControllerComponent&& other) = delete;

	//functions
	void Initialize() override;
	void PhysxUpdate() override {};
	void Update() override;
	void Render() const override {};

	 void SetActions(bool active) override;

	 bool IsFacingLeft() const { return m_FacingLeft; }
private:
	//datamembers
	shared_ptr<minigin::TransformComponent> m_spTransform;
	shared_ptr<minigin::RigidBodyComponent> m_spRigid;
	shared_ptr<minigin::ColliderComponent> m_spCollider;

	float m_Speed, m_JumpPower;
	minigin::Time& m_Time;
	bool m_Initialized,m_FacingLeft;
	vector<size_t> m_ActionIds;
	minigin::InputManager& m_InputManager;

	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

	//member functions
	void MoveLeft();
	void MoveRight();
	void Jump();
};

