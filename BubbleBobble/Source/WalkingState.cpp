#include "WalkingState.h"
#include <iostream>

TestStates WalkingState::Update()
{
	if (m_AssSlapped) return TestStates::jumping;
	
	return TestStates::walking;
}

void WalkingState::Render() const
{
}

void WalkingState::StartAction()
{
	std::cout << "Start walking\n";
}

void WalkingState::EndAction()
{
	std::cout << "end walking\n";
}

void WalkingState::SlapAss()
{
	m_AssSlapped = true;
}
