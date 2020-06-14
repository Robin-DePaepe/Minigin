#pragma once
#include <iostream> 
#include <vector>
#include <windows.h>
#include "Logger.h"
#include "GameObject.h"

class ZenChan final : public minigin::GameObject
{
public:
	ZenChan(const glm::vec2& pos, bool isMad = false, const wstring& name = L"Enemy");


private:

};

