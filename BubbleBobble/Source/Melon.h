#pragma once
#include <iostream> 
#include <vector>
#include <windows.h>
#include "Logger.h"
#include "GameObject.h"

class Melon final : public minigin::GameObject
{
public:
 Melon(const glm::vec2& pos,const wstring& name = L"Pickup");

 int GetScore() const { return m_Score; }

private:
    int m_Score;
};

