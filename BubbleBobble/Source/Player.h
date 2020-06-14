#pragma once
#include <iostream> 
#include <vector>
#include <windows.h>
#include "Logger.h"
#include "GameObject.h"
#include "Command.h"
#include "GameObject.h"
#include <InputManager.h>

class Bubble;
class Player;
class MovementControllerComponent;

class FireCommand final : public minigin::Command
{
public:
	FireCommand(Player* pObj, void(Player::* pFucntion)())
		:Command{}
		, m_Obj{ pObj }
		, m_pFucntion{ pFucntion }
	{};

	virtual void Execute()  override;
	virtual void Undo() override {};
private:
	Player* m_Obj;
	void(Player::* m_pFucntion)();
};

class Player final : public minigin::GameObject
{
public:
	Player(const glm::vec2& pos, int moveLeftButton, minigin::ControllerButton moveLeftButtonC, int moveRightButton, minigin::ControllerButton moveRightButtonC
		, int jumpButton, minigin::ControllerButton jumpButtonC, int fireButton, minigin::ControllerButton fireButtonC,const wstring& name = L"Player");

	//functions
	virtual void SetActions(bool active) override;
	virtual void OnTriggerStay(GameObject* other) override;

	shared_ptr<GameObject> GetBubble();

private:
	//datamembers
	unsigned int m_Lives;
	size_t m_FireId;

	shared_ptr<MovementControllerComponent> m_spMovement;
	shared_ptr<Bubble> m_spBubble;
	//functions
	void FireBubble();
};

