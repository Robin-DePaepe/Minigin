#pragma once
#include "StateManager.h"

enum  class TestStates
{
	walking, idle, jumping
};

class TestStatesManager : public StateManager<TestStates>
{
public:
	TestStatesManager() = default;
	void SlapAss();

};

