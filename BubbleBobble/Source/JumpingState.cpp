#include "JumpingState.h"
#include <iostream>

TestStates JumpingState::Update()
{
	--counter;

	if (counter == 0)
	{
		m_AssSlapped = false;
		return TestStates::walking;
	}

	return TestStates::jumping;
}

void JumpingState::Render() const
{
}

void JumpingState::StartAction()
{
	std::cout << "Start jumping\n";
	counter = 250;
}

void JumpingState::EndAction()
{
	std::cout << "end jumping\n";
}

void JumpingState::SlapAss()
{
}
