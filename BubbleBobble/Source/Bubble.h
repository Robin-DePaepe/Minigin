#pragma once
#include <iostream> 
#include <vector>
#include <windows.h>
#include "Logger.h"
#include "GameObject.h"

class Bubble final : public minigin::GameObject
{
public:
	Bubble(const glm::vec2& spawnpos, bool goingLeft, const wstring& name = L"Bubble");

	//functions
	void OnTriggerStay(GameObject* other) override;
	void Update() override;

private:
	//datamembers
	const float m_MaxSurviveTime, m_MaxCatchTime, m_FireSpeed, m_FloatingSpeed;
	float m_Timer, m_Dir;
};

