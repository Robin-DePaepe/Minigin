#pragma once
#include "BaseComponent.h"
#include "Command.h"
#include "Time.h"
#include <memory>

#pragma region MovementCommands
class MoveLeftCommand : public Command
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

class MoveRightCommand : public Command
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

class JumpCommand : public Command
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


class MovementControllerComponent final : public BaseComponent
{
public:
	//rule of 5
	MovementControllerComponent(float speed, float jumpPower, int moveLeftButton,int moveRightButton, int jumpButton);
	~MovementControllerComponent() = default;

	MovementControllerComponent(const MovementControllerComponent& other) = delete;
	MovementControllerComponent(MovementControllerComponent&& other) = delete;
	MovementControllerComponent& operator=(const MovementControllerComponent& other) = delete;
	MovementControllerComponent& operator=(MovementControllerComponent&& other) = delete;

	void Update() override;
	void Render() const override {};

private:
	float m_Speed, m_JumpPower;
	std::shared_ptr<TransformComponent> m_spTransform;
	Time& m_Time;
	//member functions
	void MoveLeft();
	void MoveRight();
	void Jump();
};

