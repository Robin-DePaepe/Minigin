#pragma once
#include <iostream> 
#include <vector>
#include <windows.h>
#include "Logger.h"
#include "GameObject.h"
#include "Command.h"
#include "GameObject.h"
#include <InputManager.h>
#include "fmod.hpp"

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
	//rule of 5
	Player(const glm::vec2& pos, int moveLeftButton, minigin::ControllerButton moveLeftButtonC, int moveRightButton, minigin::ControllerButton moveRightButtonC
		, int jumpButton, minigin::ControllerButton jumpButtonC, int fireButton, minigin::ControllerButton fireButtonC,const wstring& name = L"Player");

	~Player() = default;

	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;

	//functions
	 void SetActions(bool active) override;
	 void OnTriggerStay(GameObject* other) override;

	void Update() override;

	shared_ptr<GameObject> GetBubble();

private:
	//datamembers
	unsigned int m_Lives;
	size_t m_FireId;
	int m_Score;

	shared_ptr<MovementControllerComponent> m_spMovement;
	shared_ptr<Bubble> m_spBubble;

	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

	//player hit vars
	const float m_HitProtection;
	float m_Timer;
	bool m_Protected;
	//functions
	void FireBubble();
};

